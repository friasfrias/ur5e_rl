#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
import numpy as np
import os
import cv2
from cv_bridge import CvBridge
import math
import time

ângulos_juntas = [
    (1.58, -63.36, -116.17, -89.45, 88.42, 71.14),
    (-15.33, -63.73, -114.85, -90.29, 96.57, 61.26),
    (-5.96, -74.27, -102.26, -95.45, 90.41, 82.78),
    (16.95, -67.09, -104.82, -101.41, 82.95, 98.23),
    (28.03, -68.80, -110.83, -103.62, 75.62, 101.21),
    (12.72, -76.44, -110.84, -88.90, 82.46, 120.08),
    (9.80, -77.16, -94.95, -99.72, 85.07, 135.77),
    (22.16, -63.11, -91.14, -112.41, 88.95, 108.97),
    (-6.59, -64.40, -109.96, -86.30, 95.56, 128.34),
    (-20.88, -64.40, -122.56, -73.16, 101.09, 128.32),
    (-36.60, -64.41, -122.58, -75.53, 109.09, 128.30),
    (12.38, -81.68, -109.74, -89.61, 76.60, 142.10),
    (44.65, -76.91, -108.06, -107.08, 76.33, 145.55),
    (18.21, -81.63, -112.01, -91.73, 73.41, 152.01),
    (-14.73, -60.76, -122.06, -80.92, 98.96, 127.65),
    (9.22, -67.40, -85.98, -114.41, 92.14, 79.15),
    (13.07, -86.82, -79.10, -119.48, 93.89, 90.41),
    (1.66, -91.53, -75.91, -113.07, 92.19, 92.66),
    (9.92, -70.26, -68.44, -129.75, 89.90, 75.80),
    (46.26, -80.76, -68.46, -132.04, 83.05, 109.36),
    (53.17, -82.99, -84.16, -118.84, 79.50, 121.57),
    (53.04, -82.91, -84.16, -126.72, 73.69, 125.98),
    (39.42, -68.58, -81.17, -129.73, 70.02, 97.44),
    (-42.33, -69.69, -89.02, -111.44, 114.46, 82.96),
]

def graus_para_radianos(juntas_graus):
    return [math.radians(angulo) for angulo in juntas_graus]

class CapturaCalibracao(Node):
    def __init__(self):
        super().__init__('captura_calibracao')
        self.publisher = self.create_publisher(JointTrajectory, '/ur5e_controller/joint_trajectory', 10)
        self.bridge = CvBridge()
        self.ultima_imagem = None
        self.recebida_imagem = False
        self.subscription = self.create_subscription(Image, '/camera/color/image_raw', self.callback_imagem, 10)
        self.output_dir = os.path.expanduser('~/ros2_ws/src/capturas')
        os.makedirs(self.output_dir, exist_ok=True)

    def callback_imagem(self, msg):
        try:
            self.ultima_imagem = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.recebida_imagem = True
        except Exception as e:
            self.get_logger().error(f"Erro ao converter imagem: {e}")

    def esperar_imagem(self, timeout=5.0):
        """Espera até que uma imagem seja recebida ou o timeout expire"""
        self.recebida_imagem = False
        t0 = time.time()
        while rclpy.ok() and not self.recebida_imagem and (time.time() - t0) < timeout:
            rclpy.spin_once(self, timeout_sec=0.1)
        return self.recebida_imagem

    def mover_e_capturar(self):
        for i, config_graus in enumerate(ângulos_juntas):
            config_rad = graus_para_radianos(config_graus)
            traj = JointTrajectory()
            traj.joint_names = [
                'shoulder_pan_joint', 'shoulder_lift_joint', 'elbow_joint',
                'wrist_1_joint', 'wrist_2_joint', 'wrist_3_joint'
            ]
            point = JointTrajectoryPoint()
            point.positions = config_rad
            point.time_from_start.sec = 2
            traj.points.append(point)
            self.publisher.publish(traj)
            self.get_logger().info(f"[{i+1}/24] Enviado movimento para o robô.")

            time.sleep(5.0)  # Esperar que o robô estabilize

            if self.esperar_imagem():
                filename = os.path.join(self.output_dir, f'calib_{i:02d}.png')
                cv2.imwrite(filename, self.ultima_imagem)
                self.get_logger().info(f"Imagem guardada: {filename}")
            else:
                self.get_logger().warn("Imagem não recebida a tempo.")

def main(args=None):
    rclpy.init(args=args)
    node = CapturaCalibracao()
    node.mover_e_capturar()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
