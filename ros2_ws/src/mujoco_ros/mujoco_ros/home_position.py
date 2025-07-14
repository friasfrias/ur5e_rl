#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
import time

class HomePublisher(Node):
    def __init__(self):
        super().__init__('home_publisher')
        self.pub = self.create_publisher(
            JointTrajectory,
            '/ur5e_controller/joint_trajectory',
            10
        )
        # timer lento: tenta a cada 0.5s
        self.timer = self.create_timer(0.5, self.send_home)
        self.sent = False

    def send_home(self):
        if self.sent:
            rclpy.shutdown()
            return

        # só envia quando houver pelo menos 1 subscriber
        if self.pub.get_subscription_count() == 0:
            self.get_logger().info('Aguardando controller ativo...')
            return

        traj = JointTrajectory()
        traj.joint_names = [
            'shoulder_pan_joint','shoulder_lift_joint','elbow_joint',
            'wrist_1_joint','wrist_2_joint','wrist_3_joint'
        ]
        pt = JointTrajectoryPoint()
        pt.positions = [-1.5708, -1.5708, 1.5708, -1.5708, 0.0, 1.5708]
        pt.time_from_start.sec = 2
        traj.points = [pt]

        self.pub.publish(traj)
        self.get_logger().info('⚡ Pose HOME enviada!')
        self.sent = True

def main():
    rclpy.init()
    node = HomePublisher()
    rclpy.spin(node)

if __name__ == '__main__':
    main()

