# balance_env.py

import os
import sys
import subprocess
import gymnasium as gym
from gym import spaces
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Image
from geometry_msgs.msg import Vector3
from std_srvs.srv import Trigger
import numpy as np
import time
from cv_bridge import CvBridge, CvBridgeError
from vision import detect_pattern

class BalanceEnvDiscrete(gym.Env, Node):
    """
    Ambiente Gym ROS para balancear objeto com UR5e + MuJoCo em MATLAB.

    Comunica via ROS2:
      • Subscriber `angles` (Float32MultiArray) para [angle_x, angle_z]
      • Publisher `rl_delta` (Vector3) para deslocamento cartesiano do end-effector
      • Client `reset_simulation` (Trigger) para reiniciar o simulador MATLAB+MuJoCo

    Quando instanciado, lança `main.py` de simulação em background, abrindo as janelas.
    """

    def __init__(
        self,
        sim_script_path,
        survival_rate = 1,
        k = 10.0,
        delta = 0.01,
        reward_limit = 1.0,
        nx = 5,
        ny = 21,
        launch_gui=True
    ):
        
        # prepara o ambiente para off-screen se launch_gui for False
        env = os.environ.copy()
        if not launch_gui:
            # força uso de EGL (ou OSMesa, consoante a tua instalação)
            env['MUJOCO_GL'] = 'egl'  
            # alternativo: env['MUJOCO_GL'] = 'osmesa'

        # arranca o main.py com este ambiente
        cmd = [sys.executable, sim_script_path]
        self._sim_proc = subprocess.Popen(cmd, env=env)
        
        # --- 1) Inicializa Gym e ROS2 Node ---
        gym.Env.__init__(self)
        rclpy.init()
        Node.__init__(self, 'UR5e Balance with MuJoCo')

        # --- 2) Spaces ---
        self.action_space = spaces.Discrete(5)
        low = np.array([-np.pi, -np.pi], dtype=np.float32)
        high = np.array([ np.pi,  np.pi], dtype=np.float32)
        self.observation_space = spaces.Box(low, high, dtype=np.float32)


        self.survival_rate = survival_rate
        self._last_time = time.monotonic()

        # --- 3) Parâmetros de reward e ação ---
        self.k = k
        self.delta = delta
        self.reward_limit = reward_limit
        self.cumulative_reward = 0.0
        self.nx = nx
        self.ny = ny

        # 4) Setup CV bridge e armazenamento de imagens
        self._bridge = CvBridge()
        self._latest_rgb = None

        # --- 4) Subscriber de ângulos (vision.py) ---
        self._last_angles = np.zeros(2, dtype=np.float32)
        self._angle_sub = self.create_subscription(
            Float32MultiArray,
            '/angles',
            self._angle_cb,
            10,
        )

        # Subscriber para imagens RGB da câmara RealSense
        self._img_sub = self.create_subscription(
            Image,
            '/camera/color/image_raw',
            self._image_cb,
            10,
        )

        # --- 5) Publisher de delta cartesiano ---
        self._delta_pub = self.create_publisher(
            Vector3,
            '/rl_delta',
            10,
        )

        # --- 6) Cliente de serviço para reset ---
        self._reset_cli = self.create_client(
            Trigger,
            '/reset_simulation',
        )

    def _angle_cb(self, msg: Float32MultiArray):
        # Atualiza última observação dos ângulos [angle_x, angle_z] (radianos)
        data = np.array(msg.data, dtype=np.float32)
        if data.size >= 2:
            self._last_angles = data[:2]

    def _image_cb(self, msg: Image):
        # Converte ROS Image -> OpenCV RGB
        try:
            cv_img = self._bridge.imgmsg_to_cv2(msg, 'rgb8')
            self._latest_rgb = cv_img
        except CvBridgeError:
            pass

    def reset(self):
        # Reset acumulador de recompensa
        self.cumulative_reward = 0.0
        self._latest_rgb = None    

        self._last_time = time.monotonic()  

        # Chama serviço de reset do simulador
        if not self._reset_cli.wait_for_service(timeout_sec=1.0):
            raise RuntimeError('Serviço /reset_simulation indisponível')
        
        fut = self._reset_cli.call_async(Trigger.Request())
        rclpy.spin_until_future_complete(self, fut)

        # Aguarda primeira mensagem de ângulos
        while np.allclose(self._last_angles, 0.0):
            rclpy.spin_once(self, timeout_sec=0.01)

        # Aguarda primeira imagem válida
        while self._latest_rgb is None:
            rclpy.spin_once(self, timeout_sec=0.01)
        
        return self._last_angles.copy(), {}

    def step(self, action):

        now = time.monotonic()
        dt = now - self._last_time
        self._last_time = now

        # 1) Publica delta cartesiano para MATLAB
        deltas = {
            0: (-self.delta,  0.0, 0.0),  # esquerda
            1: (+self.delta,  0.0, 0.0),  # direita
            2: (0.0, +self.delta,  0.0),  # frente
            3: (0.0, -self.delta,  0.0),  # trás
            4: (0.0,  0.0, 0.0),          # nula
        }
        dx, dy, dz = deltas[int(action)]
        msg = Vector3(x=dx, y=dy, z=dz)
        self._delta_pub.publish(msg)

        # 2) Aguarda atualização dos ângulos
        prev = self._last_angles.copy()
        while np.allclose(self._last_angles, prev):
            rclpy.spin_once(self, timeout_sec=0.01)
        obs = self._last_angles.copy()

        # Aguarda nova imagem
        prev_img = self._latest_rgb
        while self._latest_rgb is prev_img:
            rclpy.spin_once(self, timeout_sec=0.01)
        rgb = self._latest_rgb

        # 3) Detecta pattern
        pattern_ok = detect_pattern(rgb, self.nx, self.ny)


        # 4) Calcula reward e acumula
        θx, θz = obs
        r_angle = np.exp(-self.k * (θx**2 + θz**2)) - 1.0
        survival_bonus = self.survival_rate * dt

        reward = survival_bonus + r_angle
        self.cumulative_reward += reward

        terminated = (not pattern_ok) or (self.cumulative_reward >= self.reward_limit)
        truncated = False

        return obs, reward, terminated, truncated, {}

    def render(self, mode='human'):
        # A simulação gráfica roda em main.py, não fazer nada aqui
        pass

    def close(self):
        # Fecha o nó ROS e encerra o processo de simulação
        try:
            self.destroy_node()
            rclpy.shutdown()
        except Exception:
            pass
        if hasattr(self, '_sim_proc'):
            self._sim_proc.terminate()

if __name__ == '__main__':
    sim_path = os.path.join(os.path.dirname(__file__), 'main.py')
    env = BalanceEnvDiscrete(
        sim_script_path=sim_path,
        reward_limit=2.0,
        nx=5, ny=21
    )

    # Reset inicial com seed opcional
    observation, info = env.reset()
    print('Observação inicial:', observation)

    done = False
    total_reward = 0.0
    for step in range(1000):
        action = env.action_space.sample()
        observation, reward, done, info = env.step(action)
        total_reward += reward
        print(f"Passo {step}: ação={action}, obs={observation}, recompensa={reward:.3f}, total={total_reward:.3f}")
        if done:
            print(f"Episódio terminado no passo {step+1} com recompensa total {total_reward:.3f}")
            observation, info = env.reset()
            total_reward = 0.0

    env.close()
