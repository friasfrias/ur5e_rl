import os
import sys
import time
import numpy as np
import gymnasium as gym
import mujoco
import rclpy
from rclpy.node import Node

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
from vision import detect_pattern


class BalanceEnv(gym.Env):
    def __init__(self, render_window=True):
        super().__init__()
        self.render_window = render_window

        # === ROS2 Node ===
        rclpy.init(args=None)
        self.node = rclpy.create_node('balance_env_node')
        self.publisher = self.node.create_publisher(Vector3, '/rl_delta', 10)

        # --- Subscriber de ângulos (vision.py) ---
        self._last_angles = np.zeros(2, dtype=np.float32)
        self._angle_sub = self.node.create_subscription(
            Float32MultiArray, '/angles', self._angle_cb, 10
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
        self.obs_clip_deg = 50.0  # mapeia ±50° -> ±1 (ajusta se precisares)
        self.observation_space = gym.spaces.Box(low=-1.0, high=1.0, shape=(2,), dtype=np.float32)
        self.action_space      = gym.spaces.Box(low=-1.0,  high=1.0,  shape=(2,), dtype=np.float32)

        # === Reward configuration ===
        self.dt = self.model.opt.timestep
        self.max_steps = 5000
        self.current_step = 0
        self.cumulative_reward = 0.0

        # (mantém parâmetro de “ok zone”, mas a reward foi melhorada lá em baixo)
        self.theta_ok = 5.0

        # Janela de silêncio pós-reset (mantido)
        self._no_cmd_until_ns = 0
        self._grace_steps = 0
        self._just_reset = False

        if self.render_window:
            if not glfw.init():
                raise RuntimeError("Falha ao inicializar GLFW")
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

            # Gate para bloquear trajectórias durante reset
            self.ignore_joint_updates = False

            # Publishers / Subscribers
            self.bridge = CvBridge()
            self.rgb_pub   = self.node.create_publisher(Image, '/camera/color/image_raw', 10)
            self.depth_pub = self.node.create_publisher(Image, '/camera/depth/image_raw', 10)

            self.node.create_subscription(JointTrajectory, '/ur5e_controller/joint_trajectory', self.cb_trajectory, 10)
            self.js_pub = self.node.create_publisher(JointState, '/joint_states', 10)
            self.reset_pub = self.node.create_publisher(Bool, '/rl_reset', 10)

    # ====== Callbacks simples ======

    def _obs_from_angles(self, angles_deg: np.ndarray) -> np.ndarray:
        # normaliza para [-1, 1]
        return np.array([
            np.clip(angles_deg[0] / self.obs_clip_deg, -1.0, 1.0),
            np.clip(angles_deg[1] / self.obs_clip_deg, -1.0, 1.0),
        ], dtype=np.float32)
    
    def _angle_cb(self, msg: Float32MultiArray):
        data = np.array(msg.data, dtype=np.float32)
        if data.size >= 2:
            self._last_angles = data[:2]

    # ====== Reward ======
    # CHANGED: reward quadrática em radianos + bónus vivo pequeno
    def _compute_reward(self, alpha_deg, beta_deg):
        alpha = np.deg2rad(alpha_deg)
        beta  = np.deg2rad(beta_deg)
        angle_cost = 2 * (alpha*alpha + beta*beta)   # ganho moderado
        alive_bonus = 0.01                           # pequeno bónus por passo
        return alive_bonus - angle_cost

    # ====== Aplicação de trajectórias ======
    def cb_trajectory(self, msg):
        if self.ignore_joint_updates:
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

    # ====== Reset ======
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)

        # Gate ON: ignorar trajectórias durante reset
        self.ignore_joint_updates = True

        # Repor estado dinâmico
        self.data.qpos[:] = self.qpos_home.copy()
        self.data.qvel[:] = 0.0
        self.data.ctrl[:6] = self.qpos_home[:6]
        mujoco.mj_forward(self.model, self.data)

        self.cumulative_reward = 0.0
        self.current_step = 0
        self.pattern_detected = False

        # Atualizar imagem e detetar padrão
        self.capture_rgb_and_publish()
        self.pattern_detected = detect_pattern(self.last_rgb, nx=5, ny=21)

        # janela de silêncio curta para evitar “picos” pós-reset (mantido)
        now_ns = self.node.get_clock().now().nanoseconds
        self._no_cmd_until_ns = now_ns + int(0.35 * 1e9)
        self._grace_steps = 8
        self._just_reset = True

        # reabrir gate antes de sair do reset
        self.ignore_joint_updates = False

        angles = np.asarray(self._last_angles, dtype=np.float32)
        obs = self._obs_from_angles(angles)
        return obs, {}

    # ====== Step ======
    def step(self, action):
        # 1) Publica ação primeiro (com janela de silêncio)
        now_ns = self.node.get_clock().now().nanoseconds
        block_cmds = (now_ns < self._no_cmd_until_ns) or (self._grace_steps > 0)

        # CHANGED: dmax mais pequeno
        dmax = 0.005  # m/step
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
        self.capture_rgb_and_publish()

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

        # Reabrir gate no 1º step após reset (mantido)
        if self._just_reset:
            self.ignore_joint_updates = False
            self._just_reset = False

        # Atualiza padrão periodicamente (mantido)
        if self.current_step % 10 == 0:
            self.pattern_detected = detect_pattern(self.last_rgb, nx=5, ny=21)
        pattern_ok = self.pattern_detected

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
