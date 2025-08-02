import os
import sys
import gymnasium as gym
import numpy as np
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Vector3
from std_srvs.srv import Trigger
import subprocess
import time

class BalanceEnvTD3(gym.Env, Node):
    def __init__(self,
                 sim_script_path,
                 delta=0.01,
                 survival_rate=1.0,
                 k=10.0,
                 reward_limit=1.0,
                 launch_gui=False):

        # --- Configura ambiente headless se necessário ---
        env = os.environ.copy()
        if not launch_gui:
            env["MUJOCO_GL"] = "egl"

        # --- Lançar simulador (main.py) ---
        cmd = [sys.executable, sim_script_path]
        self._sim_proc = subprocess.Popen(cmd, env=env)

        # --- Inicializar Gym e ROS2 Node ---
        gym.Env.__init__(self)
        rclpy.init()
        Node.__init__(self, 'td3_balance_env')

        # --- Parâmetros ---
        self.delta = delta
        self.k = k
        self.reward_limit = reward_limit
        self.survival_rate = survival_rate
        self.cumulative_reward = 0.0

        self.prev_dx = 0.0
        self.prev_dy = 0.0
        self._last_time = time.monotonic()

        # --- Observation: [dx, dy, prev_dx, prev_dy] ---
        self.observation_space = gym.spaces.Box(
            low=np.array([-1.0, -1.0, -1.0, -1.0], dtype=np.float32),
            high=np.array([1.0, 1.0, 1.0, 1.0], dtype=np.float32),
            dtype=np.float32
        )

        # --- Action: continuous dx, dy ---
        self.action_space = gym.spaces.Box(
            low=np.array([-1.0, -1.0], dtype=np.float32),
            high=np.array([1.0, 1.0], dtype=np.float32),
            dtype=np.float32
        )

        # --- Subscrever aos ângulos ---
        self._angles = np.zeros(2, dtype=np.float32)
        self._angle_sub = self.create_subscription(
            Float32MultiArray,
            '/angles',
            self._angle_cb,
            10
        )

        # --- Publicar deslocamento ---
        self._delta_pub = self.create_publisher(Vector3, '/rl_delta', 10)

        # --- Serviço de reset ---
        self._reset_cli = self.create_client(Trigger, '/reset_simulation')

    def _angle_cb(self, msg):
        data = np.array(msg.data, dtype=np.float32)
        if data.size >= 2:
            self._angles = data[:2]

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        self._last_time = time.monotonic()
        self.prev_dx = 0.0
        self.prev_dy = 0.0
        self.cumulative_reward = 0.0

        # Reset da simulação via serviço ROS
        if not self._reset_cli.wait_for_service(timeout_sec=1.0):
            raise RuntimeError("Serviço /reset_simulation indisponível")
        fut = self._reset_cli.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut)

        # Esperar novos ângulos válidos
        while np.allclose(self._angles, 0.0):
            rclpy.spin_once(self, timeout_sec=0.01)

        obs = np.array([0.0, 0.0, 0.0, 0.0], dtype=np.float32)
        return obs, {}

    def step(self, action):
        dx = float(np.clip(action[0], -1.0, 1.0)) * self.delta
        dy = float(np.clip(action[1], -1.0, 1.0)) * self.delta
        dt = time.monotonic() - self._last_time
        self._last_time = time.monotonic()

        # Enviar deslocamento
        msg = Vector3(x=dx, y=dy, z=0.0)
        self._delta_pub.publish(msg)

        # Esperar atualização dos ângulos
        old_angles = self._angles.copy()
        while np.allclose(self._angles, old_angles):
            rclpy.spin_once(self, timeout_sec=0.01)

        θx, θz = self._angles

        # Calcular reward
        r_angle = np.exp(-self.k * (θx**2 + θz**2)) - 1.0
        survival_bonus = self.survival_rate * dt
        reward = r_angle + survival_bonus
        self.cumulative_reward += reward

        # Definir observação
        obs = np.array([dx, dy, self.prev_dx, self.prev_dy], dtype=np.float32)
        self.prev_dx = dx
        self.prev_dy = dy

        # Terminar se reward limite ou padrão perdido
        terminated = self.cumulative_reward >= self.reward_limit
        truncated = False

        return obs, reward, terminated, truncated, {}

    def close(self):
        try:
            self.destroy_node()
            rclpy.shutdown()
        except Exception:
            pass
        if hasattr(self, '_sim_proc'):
            self._sim_proc.terminate()
