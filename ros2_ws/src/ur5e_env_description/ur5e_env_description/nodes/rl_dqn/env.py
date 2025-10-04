import os
import gymnasium as gym
import numpy as np
import mujoco
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Vector3
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Bool
import OpenGL.GL as gl
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import glfw
import time

import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from vision import detect_pattern


class BalanceEnv(gym.Env):
    def __init__(self, render_window=True):
        super().__init__()
        self.render_window = render_window

        # === ROS2 Node ===
        rclpy.init(args=None)
        self.node = rclpy.create_node('balance_env_node')
        self.delta_pub = self.node.create_publisher(Vector3, '/rl_delta', 10)

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

        self.qpos_home = self.data.qpos.copy()
        self.qpos_home[:6] = [0, -1.745, -2.26, 0.93, 1.53, 0.0]

        # === Spaces ===
        self.action_space = gym.spaces.Discrete(5)
        low  = np.array([-np.pi, -np.pi], dtype=np.float32)
        high = np.array([ np.pi,  np.pi], dtype=np.float32)
        self.observation_space = gym.spaces.Box(low, high, dtype=np.float32)

        # === Params ===
        self.delta = 0.0005
        self.k = 1.0
        self.survival_rate = 1.0
        self.dt = self.model.opt.timestep
        self.max_steps = 5000
        self.current_step = 0
        self.cumulative_reward = 0.0

        # Evita AttributeError antes da 1ª captura
        self.last_rgb = np.zeros((10, 10, 3), dtype=np.uint8)

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

            self.joint_name_to_idx = {}
            for i in range(self.model.njnt):
                name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, i)
                if name is not None:
                    self.joint_name_to_idx[name] = i

            self.ignore_joint_updates = False

            self.bridge = CvBridge()
            self.rgb_pub   = self.node.create_publisher(Image, '/camera/color/image_raw', 10)
            self.depth_pub = self.node.create_publisher(Image, '/camera/depth/image_raw', 10)

            self.node.create_subscription(JointTrajectory, '/ur5e_controller/joint_trajectory', self.cb_trajectory, 10)
            self.js_pub = self.node.create_publisher(JointState, '/joint_states', 10)

            self.reset_pub = self.node.create_publisher(Bool, '/rl_reset', 10)
            self.stab_pub  = self.node.create_publisher(Bool, '/rl_stabilized', 10)

        # === Reset / sync flags ===
        self.just_reset = False
        self.reset_delay_steps = int(0.2 / self.dt)  # pausa de estabilização
        self.delay_counter = 0
        self.stabilized = False
        self._need_sync = False  # <- handshake delta=(0,0,0) no 1º step após estabilização

    # ---------- Callbacks ----------
    def _angle_cb(self, msg: Float32MultiArray):
        data = np.array(msg.data, dtype=np.float32)
        if data.size >= 2:
            self._last_angles = data[:2]

    def cb_trajectory(self, msg):
        if not msg.points:
            return
        pt: JointTrajectoryPoint = msg.points[-1]
        for name, pos in zip(msg.joint_names, pt.positions):
            if name in self.joint_name_to_idx:
                idx = self.joint_name_to_idx[name]
                if idx < self.actuated_dofs:
                    self.data.ctrl[idx] = pos

    # ---------- Visão (render/publish) ----------
    def capture_rgb_and_publish(self):
        if not self.render_window:
            return

        glfw.make_context_current(self.window_feed)
        mujoco.mjv_updateCamera(self.model, self.data, self.feed_cam, self.scene)
        mujoco.mjv_updateScene(self.model, self.data, self.opt, None, self.feed_cam, mujoco.mjtCatBit.mjCAT_ALL, self.scene)
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

    # ---------- Gym API ----------
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        self.ignore_joint_updates = True
        self.data.qpos[:] = self.qpos_home.copy()
        self.data.qvel[:] = 0.0
        self.data.ctrl[:6] = self.qpos_home[:6]
        mujoco.mj_forward(self.model, self.data)

        self.cumulative_reward = 0.0
        self.current_step = 0
        self.pattern_detected = False

        # 1ª imagem para vision
        self.capture_rgb_and_publish()
        self.pattern_detected = detect_pattern(self.last_rgb, nx=5, ny=21)

        # Janela de estabilização
        self.just_reset = True
        self.delay_counter = 0
        self.reset_pub.publish(Bool(data=True))
        self.stab_pub.publish(Bool(data=False))
        self.stabilized = False
        self._need_sync = False  # será ligado após estabilização

        obs = self._last_angles.copy()
        return obs, {}

    def step(self, action):
        # 1) janela de estabilização após reset
        if self.just_reset:
            self.delay_counter += 1
            if self.delay_counter < self.reset_delay_steps:
                # deixa “assentar” — render opcional + 1 passo sim
                if self.render_window:
                    self.capture_rgb_and_publish()
                mujoco.mj_step(self.model, self.data)
                return self._last_angles.copy(), 0.0, False, False, {}
            # terminou estabilização
            self.just_reset = False
            self.stab_pub.publish(Bool(data=True))
            self.stabilized = True
            self._need_sync = True  # <- ativa handshake no próximo step

        # 2) handshake: primeiro step após estabilização — delta zero e return imediato
        if self._need_sync:
            # envia delta 0 para rebasear o controlador externo
            self.delta_pub.publish(Vector3(x=0.0, y=0.0, z=0.0))
            mujoco.mj_step(self.model, self.data)
            rclpy.spin_once(self.node, timeout_sec=0.002)  # curtinho
            if self.render_window:
                self.capture_rgb_and_publish()
            self._need_sync = False
            # não conta passo, nem calcula reward ainda
            return self._last_angles.copy(), 0.0, False, False, {}

        # 3) passo normal
        rclpy.spin_once(self.node, timeout_sec=0.005)

        # opcional: avançar sim antes/depois de publicar
        mujoco.mj_step(self.model, self.data)

        # (render opcional)
        if self.render_window:
            self.capture_rgb_and_publish()

        # publicar joint states (leve)
        stamp = self.node.get_clock().now().to_msg()
        js = JointState()
        js.header.stamp = stamp
        js.name     = list(self.joint_name_to_idx.keys())[:6]
        js.position = self.data.qpos[:6].tolist()
        js.velocity = self.data.qvel[:6].tolist()
        js.effort   = self.data.qfrc_applied[:6].tolist()
        self.js_pub.publish(js)

        # visão: check padrão de N em N passos
        if self.current_step % 10 == 0 and self.render_window:
            self.pattern_detected = detect_pattern(self.last_rgb, nx=5, ny=21)

        # mapear ação discreta -> delta
        deltas = {
            0: (-self.delta,  0.0, 0.0),
            1: (+self.delta,  0.0, 0.0),
            2: (0.0, +self.delta,  0.0),
            3: (0.0, -self.delta,  0.0),
            4: (0.0,  0.0, 0.0),
        }
        dx, dy, dz = deltas[int(action)]
        self.delta_pub.publish(Vector3(x=dx, y=dy, z=dz))

        # 1 passo de sim após comando (efeito rápido)
        mujoco.mj_step(self.model, self.data)

        # obs + reward
        obs = self._last_angles.copy()
        alpha, beta = obs
        angle_penalty = alpha**2 + beta**2
        r_angle = np.exp(-self.k * angle_penalty)          # ∈ (0,1]
        survival_bonus = self.survival_rate * self.dt      # ~constante pequena
        reward = r_angle + survival_bonus

        self.cumulative_reward += reward
        self.current_step += 1

        terminated = self.current_step >= self.max_steps or not self.pattern_detected
        truncated = False

        return obs, reward, terminated, truncated, {}

    # ---------- util ----------
    def close(self):
        self.node.destroy_node()
        rclpy.shutdown()
        mujoco.mj_deleteData(self.data)
        if self.render_window:
            glfw.destroy_window(self.window_feed)
            glfw.terminate()

    def render(self):
        pass
