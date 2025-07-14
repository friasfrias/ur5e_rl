#!/usr/bin/env python3

import os
import time
import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge


class CaptureCamNode(Node):
    def __init__(self):
        super().__init__('capture_cam')
        self.bridge = CvBridge()
        self.rgb_msg = None
        self.depth_msg = None
        self.counter = 0
        self.output_dir = os.path.expanduser('~/ros2_ws/src/capturas_realsense')
        os.makedirs(self.output_dir, exist_ok=True)

        # Subscrever tópicos de imagem
        self.create_subscription(
            Image,
            '/camera/color/image_raw',
            self.rgb_callback,
            10
        )
        self.create_subscription(
            Image,
            '/camera/depth/image_raw',
            self.depth_callback,
            10
        )

        # Janelas OpenCV
        cv2.namedWindow('RGB Full-Res', cv2.WINDOW_NORMAL)
        cv2.namedWindow('Depth Full-Res', cv2.WINDOW_NORMAL)
        cv2.resizeWindow('RGB Full-Res', 1280, 720)
        cv2.resizeWindow('Depth Full-Res', 1280, 720)

        self.get_logger().info(
            'CaptureCamNode inicializado. Pressiona "c" para capturar, "q" para sair.'
        )

    def rgb_callback(self, msg: Image):
        self.rgb_msg = msg

    def depth_callback(self, msg: Image):
        self.depth_msg = msg

    def run(self):
        try:
            while rclpy.ok():
                rclpy.spin_once(self, timeout_sec=0.1)

                # Mostrar RGB se disponível
                if self.rgb_msg:
                    cv_img = self.bridge.imgmsg_to_cv2(self.rgb_msg, 'rgb8')
                    bgr = cv2.cvtColor(cv_img, cv2.COLOR_RGB2BGR)
                    cv2.imshow('RGB Full-Res', bgr)

                # Mostrar Depth se disponível
                if self.depth_msg:
                    depth = self.bridge.imgmsg_to_cv2(self.depth_msg, '32FC1')
                    # Normalizar para visualização
                    d_norm = np.nan_to_num(depth, nan=0.0)
                    d_norm = cv2.normalize(d_norm, None, 0, 255, cv2.NORM_MINMAX)
                    depth_uint8 = d_norm.astype(np.uint8)
                    cv2.imshow('Depth Full-Res', depth_uint8)

                key = cv2.waitKey(1) & 0xFF
                if key == ord('c'):
                    self.capture_images()
                elif key == ord('q'):
                    break
        except KeyboardInterrupt:
            pass
        finally:
            cv2.destroyAllWindows()
            self.destroy_node()

    def capture_images(self):
        if self.rgb_msg is None or self.depth_msg is None:
            self.get_logger().warn('Imagens ainda não recebidas.')
            return
        # Converter
        rgb = self.bridge.imgmsg_to_cv2(self.rgb_msg, 'rgb8')
        depth = self.bridge.imgmsg_to_cv2(self.depth_msg, '32FC1')

        base = os.path.join(self.output_dir, f'capture_{self.counter:03d}')
        # Guardar RGB
        cv2.imwrite(base + '_color.png', cv2.cvtColor(rgb, cv2.COLOR_RGB2BGR))
        # Guardar depth cru em .npy
        np.save(base + '_depth.npy', depth)
        # Guardar depth para visualização
        d_norm = np.nan_to_num(depth, nan=0.0)
        d_norm = cv2.normalize(d_norm, None, 0, 255, cv2.NORM_MINMAX)
        cv2.imwrite(base + '_depth.png', d_norm.astype(np.uint8))

        self.get_logger().info(
            f'Guardado: {base}_color.png, _depth.png, _depth.npy'
        )
        self.counter += 1


def main(args=None):
    rclpy.init(args=args)
    node = CaptureCamNode()
    node.run()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
