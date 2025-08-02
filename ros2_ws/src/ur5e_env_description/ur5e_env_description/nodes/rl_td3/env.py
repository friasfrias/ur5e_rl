import os
import gymnasium as gym
import numpy as np
import mujoco
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Vector3
from std_msgs.msg import Float32MultiArray
from vision import detect_pattern

class BalanceEnv(gym.Env):
    def __init__(self):
        super().__init__()

        # === ROS2 Node ===
        rclpy.init(args=None)
        self.node = rclpy.create_node('balance_env_node')
        self.publisher = self.node.create_publisher(Vector3, '/rl_delta', 10)
        self.node.create_subscription(Float32MultiArray, 'displacements', self.cb_displacements, 10)

        # === Displacement variables ===
        self.dx = 0.0
        self.dz = 0.0
        self.prev_dx = 0.0
        self.prev_dz = 0.0

        # === Load MuJoCo model ===
        model_path = os.path.join(
            os.getenv("HOME"),
            "ros2_ws", "src", "ur5e_env_description", "models", "ur5e_env.xml"
        )
        self.model = mujoco.MjModel.from_xml_path(model_path)
        self.data = mujoco.MjData(self.model)

        # Home joint positions for the UR5e robot
        self.qpos_home = np.zeros_like(self.data.qpos)
        self.qpos_home[:6] = [0, -1.745, -2.26, 0.93, 1.53, 0.0]

        # === Observation and Action Spaces ===
        # Observation = [dx, dz, previous dx, previous dz]
        self.observation_space = gym.spaces.Box(low=-1.0, high=1.0, shape=(4,), dtype=np.float32)
        # Action = [delta_x, delta_z] sent to the robot via ROS2
        self.action_space = gym.spaces.Box(low=-0.01, high=0.01, shape=(2,), dtype=np.float32)

        # === Reward configuration ===
        self.k = 10.0                     # Penalty scaling for deviation
        self.survival_rate = 0.1         # Survival bonus per timestep
        self.dt = self.model.opt.timestep
        self.max_steps = 300             # Maximum steps per episode
        self.current_step = 0
        self.cumulative_reward = 0.0

    def cb_displacements(self, msg):
        # Callback for displacement updates from vision node
        self.prev_dx = self.dx
        self.prev_dz = self.dz
        self.dx, self.dz = msg.data

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)

        # Reset robot to home configuration
        self.data.qpos[:] = self.qpos_home.copy()
        self.data.qvel[:] = 0.0
        mujoco.mj_forward(self.model, self.data)

        self.current_step = 0
        self.cumulative_reward = 0.0

        # Wait until the pattern is detected (object is visible)
        while not detect_pattern():
            rclpy.spin_once(self.node, timeout_sec=0.01)

        # Wait until a new displacement message is received
        old_dx, old_dz = self.dx, self.dz
        while np.isclose(self.dx, old_dx) and np.isclose(self.dz, old_dz):
            rclpy.spin_once(self.node, timeout_sec=0.01)

        obs = np.array([self.dx, self.dz, self.prev_dx, self.prev_dz], dtype=np.float32)
        return obs, {}

    def step(self, action):
        dx_cmd, dz_cmd = action

        # Publish action to robot through ROS2 topic
        msg = Vector3(x=float(dx_cmd), y=0.0, z=float(dz_cmd))
        self.publisher.publish(msg)

        # Wait until a new displacement message is received
        old_dx, old_dz = self.dx, self.dz
        while np.isclose(self.dx, old_dx) and np.isclose(self.dz, old_dz):
            rclpy.spin_once(self.node, timeout_sec=0.01)

        # Calculate reward: penalize angle deviation, add small bonus for surviving
        r_angle = np.exp(-self.k * (self.dx**2 + self.dz**2)) - 1.0
        survival_bonus = self.survival_rate * self.dt
        reward = r_angle + survival_bonus
        self.cumulative_reward += reward

        # Construct new observation
        obs = np.array([self.dx, self.dz, self.prev_dx, self.prev_dz], dtype=np.float32)

        # Check termination condition: max steps or lost visual pattern
        done = self.current_step >= self.max_steps or not detect_pattern()
        self.current_step += 1

        return obs, reward, done, False, {}

    def close(self):
        # Properly shutdown ROS2 and MuJoCo data
        self.node.destroy_node()
        rclpy.shutdown()
        mujoco.mj_deleteData(self.data)

    def render(self):
        pass
