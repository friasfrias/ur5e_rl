#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Vector3
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
import numpy as np
from roboticstoolbox.models import DH

class TestStraightenCube(Node):
    def __init__(self):
        super().__init__('test_straighten_cube')
        # parâmetros PID e físicos (podias declará-los como parâmetros ROS também)
        self.Kp_x, self.Ki_x, self.Kd_x = 1.0, 0.1, 0.01
        self.Kp_z, self.Ki_z, self.Kd_z = 1.0, 0.1, 0.01
        self.h  = 0.154    # altura do cubo (m)
        self.dt = 0.02     # período de controlo (s)

        # estado PID
        self.int_x = 0.0; self.prev_x = 0.0
        self.int_z = 0.0; self.prev_z = 0.0

        # configuração inicial das juntas
        self.q0 = np.array([0.0, -1.57, 1.57, 0.0, 0.0, 0.0])

        # modelo e publisher
        self.robot = DH.UR5()
        self.pub   = self.create_publisher(JointTrajectory,
                                           '/ur5e_controller/joint_trajectory', 10)

        # **Valores fixos de teste**:
        alpha = 0.087   # rad
        beta  = -0.07  # rad

        # faz o ciclo de controlo **uma única vez**
        self.apply_once(alpha, beta)

        # dá um timeout curto para garantir que a mensagem sai
        # e depois encerra o nó
        self.create_timer(0.1, self.shutdown)

    def apply_once(self, alpha, beta):
        # 1) deslocamentos geométricos
        dx = (self.h/2) * np.tan(alpha)
        dz = (self.h/2) * np.tan(beta)

        # 2) PID em task-space
        err_x, err_z = dx, dz
        self.int_x += err_x * self.dt
        self.int_z += err_z * self.dt
        der_x = (err_x - self.prev_x) / self.dt
        der_z = (err_z - self.prev_z) / self.dt

        vx = self.Kp_x*err_x + self.Ki_x*self.int_x + self.Kd_x*der_x
        vz = self.Kp_z*err_z + self.Ki_z*self.int_z + self.Kd_z*der_z

        self.prev_x, self.prev_z = err_x, err_z

        # 3) Jacobiana XZ → dq_dot
        J   = self.robot.jacob0(self.q0)[0:3, :]
        Jxz = J[[0,2], :]
        dq_dot = np.linalg.pinv(Jxz) @ np.array([vx, vz])

        # 4) integra Δq e atualiza q0
        delta_q = dq_dot * self.dt
        q_target = self.q0 + delta_q
        self.q0 = q_target.copy()

        # 5) monta e publica JointTrajectory
        traj = JointTrajectory()
        traj.joint_names = [
            'shoulder_pan_joint', 'shoulder_lift_joint', 'elbow_joint',
            'wrist_1_joint', 'wrist_2_joint', 'wrist_3_joint'
        ]
        pt = JointTrajectoryPoint()
        pt.positions = list(q_target)
        pt.time_from_start.sec     = 0
        pt.time_from_start.nanosec = int(self.dt * 1e9)
        traj.points = [pt]

        self.pub.publish(traj)
        self.get_logger().info(f'Published one-shot q_target: {np.round(q_target,3)}')

    def shutdown(self):
        self.get_logger().info('Shutting down.')
        rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    node = TestStraightenCube()
    rclpy.spin(node)

if __name__ == '__main__':
    main()
