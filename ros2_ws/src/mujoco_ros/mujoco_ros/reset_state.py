#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from mujoco_ros_msgs.srv import SetBodyPose
import time

class ResetSimState(Node):
    def __init__(self):
        super().__init__('reset_sim_state')

        # Publisher para o robô
        self.pub = self.create_publisher(JointTrajectory, '/ur5e_controller/joint_trajectory', 10)

        # Esperar para garantir que tudo arrancou
        self.get_logger().info("A aguardar 5 segundos pelo simulador e controladores...")
        time.sleep(5)

        # Enviar posição para o UR5e
        traj = JointTrajectory()
        traj.joint_names = [
            'shoulder_pan_joint',
            'shoulder_lift_joint',
            'elbow_joint',
            'wrist_1_joint',
            'wrist_2_joint',
            'wrist_3_joint'
        ]

        point = JointTrajectoryPoint()
        point.positions = [0.0, -1.5708, 1.5708, 0.0, 0.0, 0.0]
        point.time_from_start.sec = 1
        traj.points.append(point)

        self.get_logger().info("Enviando posição home para o UR5e...")
        self.pub.publish(traj)

        # Reset do objeto instável
        self.cli = self.create_client(SetBodyPose, '/mujoco/set_body_pose')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('A aguardar serviço /mujoco/set_body_pose...')

        req = SetBodyPose.Request()
        req.body_name = 'objeto_instavel'
        req.pose.position.x = -0.815
        req.pose.position.y = -0.5
        req.pose.position.z = 0.183
        req.pose.orientation.w = 1.0
        req.pose.orientation.x = 0.0
        req.pose.orientation.y = 0.0
        req.pose.orientation.z = 0.0

        self.get_logger().info("Enviando pose inicial para objeto_instavel...")
        future = self.cli.call_async(req)
        rclpy.spin_until_future_complete(self, future)

        if future.result():
            self.get_logger().info("Reset do objeto concluído.")
        else:
            self.get_logger().error("Erro ao resetar o objeto.")

        rclpy.shutdown()

def main():
    rclpy.init()
    ResetSimState()

if __name__ == '__main__':
    main()
