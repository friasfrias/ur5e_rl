import os
import sys
import time
import numpy as np
import gymnasium as gym
import mujoco
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSHistoryPolicy, QoSReliabilityPolicy, QoSDurabilityPolicy

from geometry_msgs.msg import Vector3
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from std_msgs.msg import Float32MultiArray, Bool

import OpenGL.GL as gl
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import glfw

# permitir import relativo para vision.py
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from vision_rl import detect_pattern


class BalanceEnv(gym.Env):
    def __init__(self, render_window=True):
        super().__init__()
        self.render_window = render_window

        # === ROS2 Node ===
        rclpy.init(args=None)
        self.node = rclpy.create_node('balance_env_node')

        # QoS perfis
        qos_keep1_rel = QoSProfile(
            history=QoSHistoryPolicy.KEEP_LAST, depth=1,
            reliability=QoSReliabilityPolicy.RELIABLE,
            durability=QoSDurabilityPolicy.VOLATILE
        )
        qos_keep1_be = QoSProfile(
            history=QoSHistoryPolicy.KEEP_LAST, depth=1,
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            durability=QoSDurabilityPolicy.VOLATILE
        )

        # /rl_delta → BEST_EFFORT + KEEP_LAST(1)
        self.publisher = self.node.create_publisher(Vector3, '/rl_delta', qos_keep1_be)

        # /rl_reset e /joint_states ficam RELIABLE
        self.reset_pub = self.node.create_publisher(Bool, '/rl_reset', qos_keep1_rel)
        self.js_pub    = self.node.create_publisher(JointState, '/joint_states', qos_keep1_rel)

        # --- Subscriber de ângulos (vision.py) ---
        self._last_angles = np.zeros(2, dtype=np.float32)
        self._angle_sub = self.node.create_subscription(
            Float32MultiArray, '/angles', self._angle_cb, qos_keep1_rel
        )

        # === Load MuJoCo model ===
        model_path = os.path.join(
            os.getenv("HOME"),
            "ur5e_rl", "ros2_ws", "src", "ur5e_env_description", "models", "ur5e_env.xml"
        )
        self.model = mujoco.MjModel.from_xml_path(model_path)
        self.data = mujoco.MjData(self.model)
        self.actuated_dofs = self.model.nu

        # Estado "home" (cópia do qpos completo)
        self.qpos_home = self.data.qpos.copy()
        self.qpos_home[:6] = [0, -1.745, -2.26, 0.93, 1.53, 0.0]

        # Observation / Action spaces
        self.obs_clip_deg = 90.0  # mapeia ±50° -> ±1
        self.observation_space = gym.spaces.Box(low=-1.0, high=1.0, shape=(2,), dtype=np.float32)
        self.action_space      = gym.spaces.Box(low=-1.0,  high=1.0,  shape=(2,), dtype=np.float32)

        # === Reward configuration ===
        self.dt = self.model.opt.timestep
        self.max_steps = 5000
        self.current_step = 0
        self.cumulative_reward = 0.0
        self.theta_ok = 5.0

        self.limit_deg    = 5.0      # largura da banda "ok"
        self.alive_in    = 0.3     # bónus por passo dentro da banda
        self.alive_out   = 0.1     # bónus por passo fora da banda
        self.k  = 0.002    # penalização por (excesso_deg)^2

        # Gates de silêncio pós-reset
        self._no_cmd_until_s   = 0.0     # bloqueia /rl_delta
        self._traj_gate_until_s = 0.0    # bloqueia trajectórias
        self.ignore_joint_updates = False

       # ---------- Render e publishers de imagem ----------
        if self.render_window:
            if not glfw.init():
                raise RuntimeError("Falha ao inicializar GLFW")

            # === FEED RealSense (mantém como tinhas) ===
            self.feed_w, self.feed_h = 1280, 720
            self.window_feed = glfw.create_window(self.feed_w, self.feed_h, "Feed RealSense - RL", None, None)
            if not self.window_feed:
                glfw.terminate()
                raise RuntimeError("Falha ao criar a janela GLFW")

            glfw.make_context_current(self.window_feed)
            self.ctx_feed = mujoco.MjrContext(self.model, mujoco.mjtFontScale.mjFONTSCALE_100.value)
            self.vp_feed = mujoco.MjrRect(0, 0, self.feed_w, self.feed_h)

            cam_id = mujoco.mj_name2id(self.model, mujoco.mjtObj.mjOBJ_CAMERA, b"realsense")
            self.feed_cam = mujoco.MjvCamera()
            self.feed_cam.fixedcamid = cam_id
            self.feed_cam.type = mujoco.mjtCamera.mjCAMERA_FIXED

            self.opt = mujoco.MjvOption()
            self.scene = mujoco.MjvScene(self.model, maxgeom=1000)

            self.overlay_tex = gl.glGenTextures(1)
            gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
            gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
            gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, gl.GL_RGB, self.feed_w, self.feed_h, 0, gl.GL_RGB, gl.GL_UNSIGNED_BYTE, None)
            gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

            # === NOVO: Janela PRINCIPAL do simulador (1200x900) ===
            self.sim_w, self.sim_h = 1200, 900
            self.window_main = glfw.create_window(self.sim_w, self.sim_h, "Simulador UR5e - RL", None, None)
            if not self.window_main:
                glfw.destroy_window(self.window_feed)
                glfw.terminate()
                raise RuntimeError("Falha ao criar a janela principal do simulador")

            # (Opcional) posicionar para não sobrepor
            try:
                glfw.set_window_pos(self.window_main, 60, 60)
                glfw.set_window_pos(self.window_feed, 1400, 60)  # ajusta conforme a largura do teu monitor
            except Exception:
                pass

            # Contexto + viewport da janela principal
            glfw.make_context_current(self.window_main)
            self.ctx_main = mujoco.MjrContext(self.model, mujoco.mjtFontScale.mjFONTSCALE_150.value)
            self.vp_main  = mujoco.MjrRect(0, 0, self.sim_w, self.sim_h)

            # Câmara principal (igual à usada no PID)
            self.main_cam = mujoco.MjvCamera()
            self.main_cam.lookat   = np.array([0.0, 0.0, 0.1])
            self.main_cam.distance = 2.5
            self.main_cam.azimuth  = 45
            self.main_cam.elevation= -20

            # 1º frame + eventos para evitar "not responding"
            gl.glViewport(0, 0, self.sim_w, self.sim_h)
            gl.glClearColor(0.1, 0.1, 0.1, 1.0)
            gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
            glfw.swap_buffers(self.window_main)
            glfw.poll_events()

            # Voltar ao feed (mantém o teu pipeline RGB/Depth tal e qual)
            glfw.make_context_current(self.window_feed)


            # --- Mapas de juntas e ORDEM CANÓNICA ---
            self.joint_name_to_id = {}
            for j_id in range(self.model.njnt):
                name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, j_id)
                if name:
                    self.joint_name_to_id[name] = j_id

            self.joint_order = [
                "shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",
                "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"
            ]

            # endereços corretos qpos/qvel por junta (hinge → 1 dof)
            self.qpos_addr = [int(self.model.jnt_qposadr[self.joint_name_to_id[n]]) for n in self.joint_order]
            self.qvel_addr = [int(self.model.jnt_dofadr[self.joint_name_to_id[n]]) for n in self.joint_order]

            # junta → índice de atuador em data.ctrl
            self.joint_to_actuator = {}
            for a in range(self.model.nu):
                j_id = int(self.model.actuator_trnid[a][0])
                j_name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, j_id)
                if j_name:
                    self.joint_to_actuator[j_name] = a

            # QoS para imagens: sensor data (dropável, sem backlog)
            qos_img = qos_keep1_be
            self.bridge = CvBridge()
            self.rgb_pub   = self.node.create_publisher(Image, '/camera/color/image_raw', qos_img)
            self.depth_pub = self.node.create_publisher(Image, '/camera/depth/image_raw', qos_img)

            # /ur5e_controller/joint_trajectory → RELIABLE + KEEP_LAST(1)
            self.node.create_subscription(
                JointTrajectory, '/ur5e_controller/joint_trajectory', self.cb_trajectory, qos_keep1_rel
            )
        else:
            # Mesmo sem janela, ainda precisamos destes mapas para /joint_states
            self.joint_name_to_id = {}
            for j_id in range(self.model.njnt):
                name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, j_id)
                if name:
                    self.joint_name_to_id[name] = j_id
            self.joint_order = [
                "shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",
                "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"
            ]
            self.qpos_addr = [int(self.model.jnt_qposadr[self.joint_name_to_id[n]]) for n in self.joint_order]
            self.qvel_addr = [int(self.model.jnt_dofadr[self.joint_name_to_id[n]]) for n in self.joint_order]
            self.joint_to_actuator = {}
            for a in range(self.model.nu):
                j_id = int(self.model.actuator_trnid[a][0])
                j_name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, j_id)
                if j_name:
                    self.joint_to_actuator[j_name] = a
            self.node.create_subscription(
                JointTrajectory, '/ur5e_controller/joint_trajectory', self.cb_trajectory, qos_keep1_rel
            )

    # ====== Callbacks simples ======
    def _obs_from_angles(self, angles_deg: np.ndarray) -> np.ndarray:
        return np.array([
            np.clip(angles_deg[0] / self.obs_clip_deg, -1.0, 1.0),
            np.clip(angles_deg[1] / self.obs_clip_deg, -1.0, 1.0),
        ], dtype=np.float32)

    def _angle_cb(self, msg: Float32MultiArray):
        data = np.array(msg.data, dtype=np.float32)
        if data.size >= 2:
            self._last_angles = data[:2]

    # ====== Reward ======
    def _compute_reward(self, alpha_deg, beta_deg, u=None):
        limit = self.limit_deg  # 5.0
        # excesso acima da banda em cada eixo (0 se dentro)
        alpha_excess = max(0.0, abs(alpha_deg) - limit)
        beta_excess  = max(0.0, abs(beta_deg)  - limit)
        in_interval = (alpha_excess == 0.0 and beta_excess == 0.0)

        if in_interval:
            # bónus extra dentro da banda, 0..0.2
            # normaliza ângulos à banda: 0.0 no centro, 1.0 no limite
            a = abs(alpha_deg) / limit
            b = abs(beta_deg) / limit
            # bónus quadrático, máximo 0.2 no centro, 0.0 no limite
            r_shape = 0.2 * max(0.0, 1.0 - 0.5 * (a*a + b*b))
            r = self.alive_in + r_shape  # 0.3 + [0..0.2] → [0.3..0.5]
        else:
            # fora da banda mantém exatamente a tua lógica
            angle_penalty = alpha_excess*alpha_excess + beta_excess*beta_excess
            r = self.alive_out - self.k * angle_penalty  # 0.1 - 0.002*excesso^2

        # penalização de ação opcional, se quiseres manter
        if u is not None:
            r -= 0.05 * float(np.dot(u, u))

        return float(r)



    # ====== Aplicação de trajectórias ======
    def cb_trajectory(self, msg):
        # Gate: descarta trajectórias durante o silêncio pós-reset
        if self.ignore_joint_updates or (time.monotonic() < self._traj_gate_until_s):
            return
        if not msg.points:
            return
        pt: JointTrajectoryPoint = msg.points[-1]
        for name, pos in zip(msg.joint_names, pt.positions):
            if not np.isfinite(pos):
                continue
            a_idx = self.joint_to_actuator.get(name)
            if a_idx is None or a_idx >= self.actuated_dofs:
                continue
            self.data.ctrl[a_idx] = float(pos)

    # ====== Render feed e publicar RGB/Depth ======
    def capture_rgb_and_publish(self):
        if not self.render_window:
            return
        glfw.make_context_current(self.window_feed)
        mujoco.mjv_updateCamera(self.model, self.data, self.feed_cam, self.scene)
        mujoco.mjv_updateScene(self.model, self.data, self.opt, None,
                               self.feed_cam, mujoco.mjtCatBit.mjCAT_ALL, self.scene)
        gl.glClearColor(0, 0, 0, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        mujoco.mjr_render(self.vp_feed, self.scene, self.ctx_feed)
        glfw.swap_buffers(self.window_feed)

        rgb_arr   = np.zeros((self.feed_h, self.feed_w, 3), dtype=np.uint8)
        depth_arr = np.zeros((self.feed_h, self.feed_w),   dtype=np.float32)
        mujoco.mjr_readPixels(rgb_arr, depth_arr, self.vp_feed, self.ctx_feed)

        self.last_rgb = np.flipud(rgb_arr)
        depth_arr = np.flipud(depth_arr)

        stamp = self.node.get_clock().now().to_msg()
        rgb_msg   = self.bridge.cv2_to_imgmsg(rgb_arr,   encoding='rgb8')
        depth_msg = self.bridge.cv2_to_imgmsg(depth_arr, encoding='32FC1')
        rgb_msg.header.stamp      = depth_msg.header.stamp = stamp
        rgb_msg.header.frame_id   = 'camera_color_optical_frame'
        depth_msg.header.frame_id = 'camera_depth_optical_frame'
        self.rgb_pub.publish(rgb_msg)
        self.depth_pub.publish(depth_msg)
    
    def render_main_window(self):
        if not self.render_window:
            return
        glfw.make_context_current(self.window_main)
        mujoco.mjv_updateCamera(self.model, self.data, self.main_cam, self.scene)
        mujoco.mjv_updateScene(self.model, self.data, self.opt, None,
                            self.main_cam, mujoco.mjtCatBit.mjCAT_ALL, self.scene)
        gl.glClearColor(0.1, 0.1, 0.1, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        mujoco.mjr_render(self.vp_main, self.scene, self.ctx_main)
        glfw.swap_buffers(self.window_main)


    # ====== Reset ======
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)

        # Gate ON: ignorar trajectórias durante reset (0.5 s)
        self.ignore_joint_updates = True
        self._traj_gate_until_s = time.monotonic() + 0.50

        # Repor estado dinâmico
        self.data.qpos[:] = self.qpos_home.copy()
        self.data.qvel[:] = 0.0
        self.data.ctrl[:6] = self.qpos_home[:6]
        mujoco.mj_forward(self.model, self.data)

        self.cumulative_reward = 0.0
        self.current_step = 0
        self.pattern_detected = False

        # Atualizar imagem e detetar padrão
        if self.render_window:
            self.capture_rgb_and_publish()
        self.pattern_detected = True if not hasattr(self, 'last_rgb') else detect_pattern(self.last_rgb, nx=5, ny=21)

        # Notificar reset e mandar 2 zeros (limpa “intenções” do controlador MATLAB)
        self.reset_pub.publish(Bool(data=True))
        for _ in range(2):
            self.publisher.publish(Vector3(x=0.0, y=0.0, z=0.0))
            rclpy.spin_once(self.node, timeout_sec=0.0)

        # Silêncio de /rl_delta por ~0.35 s + alguns passos de graça
        self._no_cmd_until_s = time.monotonic() + 0.35
        self._grace_steps = 8

        angles = np.asarray(self._last_angles, dtype=np.float32)
        obs = self._obs_from_angles(angles)
        return obs, {}

    # ====== Step ======
    def step(self, action):
        now = time.monotonic()

        # Reabrir gate de trajectórias quando terminar a janela
        if self.ignore_joint_updates and (now >= self._traj_gate_until_s):
            self.ignore_joint_updates = False
            self._traj_gate_until_s = 0.0

        # 1) Publica ação primeiro (com janela de silêncio)
        block_cmds = (now < self._no_cmd_until_s) or (getattr(self, "_grace_steps", 0) > 0)

        dmax = 0.015  # m/step
        a = np.clip(np.asarray(action, dtype=np.float32).reshape(2), -1.0, 1.0)
        if block_cmds:
            dx, dy = 0.0, 0.0
            if self._grace_steps > 0:
                self._grace_steps -= 1
        else:
            dx = float(a[0] * dmax)
            dy = float(a[1] * dmax)

        self.publisher.publish(Vector3(x=dx, y=dy, z=0.0))

        # pequeno spin para entregar callbacks (traj/angles) antes do step
        rclpy.spin_once(self.node, timeout_sec=0.001)

        # 2) Avança simulação e imagem
        mujoco.mj_step(self.model, self.data)
        if self.render_window:
            self.capture_rgb_and_publish()
            self.render_main_window()
            # Processar eventos das janelas (evita 'not responding')
            glfw.poll_events()

        # outro spin curtinho para apanhar /angles derivados da imagem (se existirem)
        rclpy.spin_once(self.node, timeout_sec=0.001)

        # 3) /joint_states (telemetria)
        stamp = self.node.get_clock().now().to_msg()
        js = JointState()
        js.header.stamp = stamp
        js.name     = self.joint_order
        js.position = [float(self.data.qpos[i]) for i in self.qpos_addr]
        js.velocity = [float(self.data.qvel[i]) for i in self.qvel_addr]
        js.effort   = [float(self.data.qfrc_applied[i]) for i in self.qvel_addr]
        self.js_pub.publish(js)

        # Atualiza padrão periodicamente (se houver feed)
        if self.render_window and self.current_step % 10 == 0:
            self.pattern_detected = detect_pattern(self.last_rgb, nx=5, ny=21)
        pattern_ok = self.pattern_detected if self.render_window else True

        # 4) Reward & terminação
        angles = np.asarray(self._last_angles, dtype=np.float32)
        alpha, beta = float(angles[0]), float(angles[1])
        reward = self._compute_reward(alpha, beta)

        self.current_step += 1
        terminated = (not pattern_ok) and (not block_cmds)
        truncated  = (self.current_step >= self.max_steps)

        obs = self._obs_from_angles(angles)
        return obs, reward, terminated, truncated, {}

    # ====== Close ======
    def close(self):
        self.node.destroy_node()
        rclpy.shutdown()
        mujoco.mj_deleteData(self.data)
        if self.render_window:
            glfw.destroy_window(self.window_feed)
            glfw.terminate()

    def render(self):
        pass
