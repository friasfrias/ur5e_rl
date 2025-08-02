#!/usr/bin/env python3
import os
import numpy as np

import rclpy
from rclpy.node import Node
from ament_index_python.packages import get_package_share_directory

from sensor_msgs.msg import JointState
from geometry_msgs.msg import Vector3
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

import mujoco
from mujoco import mjtObj


class LevenbergMarquardtIK:
    def __init__(self, model, data, step_size=0.5, tol=1e-3, damping=0.15):
        self.model = model
        self.data = data
        self.step_size = step_size
        self.tol = tol
        self.damping = damping

        nv = model.nv
        # jacobianos de translação e rotação
        self.jacp  = np.zeros((3, nv), dtype=np.float64)
        self.jacr = np.zeros((3, nv), dtype=np.float64)

    def clamp(self, q: np.ndarray) -> np.ndarray:
        # apenas sobre as 6 juntas do braço
        lo = self.model.jnt_range[:6, 0]
        hi = self.model.jnt_range[:6, 1]
        return np.maximum(np.minimum(q, hi), lo)

    def solve(self, goal: np.ndarray, q0: np.ndarray, body_id: int) -> np.ndarray:
        # 1) coloca q0 em data.qpos e faz FK
        self.data.qpos[:6] = q0
        mujoco.mj_forward(self.model, self.data)

        # 2) calcula erro inicial
        curr = self.data.xpos[body_id].copy()
        err  = goal - curr

        # 3) iterar até convergir
        while np.linalg.norm(err) > self.tol:
            # 3.a) recomputa jacobiano do corpo
            localpos = np.zeros(3, dtype=np.float64)  # ponto de referência no corpo
            mujoco.mj_jac(
                self.model, self.data,
                self.jacp, self.jacr,
                localpos, body_id
            )
            J    = self.jacp[:, :6]                # parte de translação apenas
            JTJ  = J.T @ J
            A    = JTJ + self.damping * np.eye(6)  # termo de regularização
            dq   = np.linalg.solve(A, J.T @ err)   # passo LM

            # 3.b) atualiza qpos e aplica clamp
            new_q = self.data.qpos[:6] + self.step_size * dq
            self.data.qpos[:6] = self.clamp(new_q)
            mujoco.mj_forward(self.model, self.data)

            # 3.c) recalcula erro
            curr = self.data.xpos[body_id].copy()
            err  = goal - curr

        return self.data.qpos[:6].copy()


class IKNode(Node):
    def __init__(self):
        super().__init__('kinematics')

        # 1) nomes e estado inicial (home) das 6 juntas UR5e
        self.joint_names = [
            'shoulder_pan_joint','shoulder_lift_joint','elbow_joint',
            'wrist_1_joint','wrist_2_joint','wrist_3_joint'
        ]
        self.q_prev = np.array([0., -1.745, -2.26, 0.93, 1.53, 0.0])

        # 2) carrega modelo MuJoCo, dados e aplica keyframe “home” (free joint incluso)
        pkg = get_package_share_directory('ur5e_env_description')
        xml = os.path.join(pkg, 'models', 'ur5e_env.xml')
        self.model = mujoco.MjModel.from_xml_path(xml)
        self.data  = mujoco.MjData(self.model)
        mujoco.mj_resetDataKeyframe(self.model, self.data, 0)
        mujoco.mj_forward(self.model, self.data)

        # 3) obtém body_id do wrist_3_link
        self.ee_body_id = mujoco.mj_name2id(
            self.model, mjtObj.mjOBJ_BODY, 'wrist_3_link'
        )

        # 4) instância do solver LM
        self.ik_solver = LevenbergMarquardtIK(
            self.model, self.data,
            step_size=0.5, tol=1e-3, damping=0.15
        )

        # 5) publisher de JointTrajectory
        self.pub = self.create_publisher(
            JointTrajectory, '/ur5e_controller/joint_trajectory', 10
        )

        # 6) subscrição de /joint_states para atualização de q_prev e FK
        self.received_js = False
        self.target_pos  = None
        self.create_subscription(
            JointState, '/joint_states', self.joint_state_cb, 10
        )

        # 7) subscrição de /rl_delta para comandos em cartesianas
        self.delta_received = False
        self.create_subscription(
            Vector3, '/rl_delta', self.delta_cb, 10
        )

        self.control_timer = None
        self.get_logger().info('IKNode iniciado – aguardando /joint_states')

    def joint_state_cb(self, msg: JointState):
        # 1) atualiza q_prev a partir do topic
        mp = dict(zip(msg.name, msg.position))
        self.q_prev = np.array([mp[n] for n in self.joint_names])

        # 2) faz FK em MuJoCo e lê posição atual do wrist_3_link
        self.data.qpos[:6] = self.q_prev
        mujoco.mj_forward(self.model, self.data)
        pos = self.data.xpos[self.ee_body_id].copy()

        # 3) na primeira chamada, define target_pos e arranca timer
        if not self.received_js:
            self.target_pos = pos
            self.get_logger().info(f"Posição inicial TCP: {pos}")
            self.control_timer = self.create_timer(0.1, self.control_loop)
            self.get_logger().info('Control loop iniciado (10 Hz)')
            self.received_js = True

    def delta_cb(self, msg: Vector3):
        d = np.array([msg.x, msg.y, msg.z])
        self.get_logger().info(f"Delta recebido: {d}")
        self.target_pos += d
        self.delta_received = True

    def control_loop(self):
        if not self.delta_received:
            return

        # resolve IK para o novo target_pos
        q_sol = self.ik_solver.solve(
            self.target_pos, self.q_prev, self.ee_body_id
        )

        # publica JointTrajectory de 1 s
        traj = JointTrajectory()
        traj.joint_names = self.joint_names
        pt = JointTrajectoryPoint()
        pt.positions = q_sol.tolist()
        pt.time_from_start.sec = 1
        traj.points = [pt]
        self.pub.publish(traj)
        self.get_logger().info(f"Publicado q_sol: {q_sol}")

        # prepara para o próximo delta
        self.q_prev        = q_sol
        self.delta_received = False


def main(args=None):
    rclpy.init(args=args)
    node = IKNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
