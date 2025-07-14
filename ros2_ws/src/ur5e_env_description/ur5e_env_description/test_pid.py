#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

class TestTrajNode(Node):
    def __init__(self):
        super().__init__('test_traj')
        self.pub = self.create_publisher(
            JointTrajectory,
            '/ur5e_controller/joint_trajectory',
            10
        )
        self.timer = self.create_timer(1.0, self.send_trajectory)

    def send_trajectory(self):
        traj = JointTrajectory()
        traj.joint_names = [
            'shoulder_pan_joint','shoulder_lift_joint','elbow_joint',
            'wrist_1_joint','wrist_2_joint','wrist_3_joint'
        ]
        # Ponto inicial é a posição atual (usa zeros como teste)
        p0 = JointTrajectoryPoint()
        p0.positions = [0.0, -1.745, -2.27, 0.93, 1.53, 0.0]
        p0.time_from_start.sec = 0
        p0.time_from_start.nanosec = 0
        # Ponto final: ligeira mudança
        p1 = JointTrajectoryPoint()
        p1.positions = [0.0, -1.2, -1.2, 0.0, 1.2, 0.0]
        p1.time_from_start.sec = 2
        p1.time_from_start.nanosec = 0
        traj.points = [p0, p1]

        self.pub.publish(traj)
        self.get_logger().info('Mensagem de teste publicada em /ur5e_controller/joint_trajectory')

def main():
    rclpy.init()
    node = TestTrajNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
