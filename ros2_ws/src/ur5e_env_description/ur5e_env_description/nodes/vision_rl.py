#!/usr/bin/env python3
import os
import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Float32MultiArray, Bool
from cv_bridge import CvBridge, CvBridgeError
from message_filters import Subscriber, ApproximateTimeSynchronizer
from ament_index_python.packages import get_package_share_directory
from rclpy.qos import qos_profile_sensor_data

def build_objp(nx, ny, square_size):
    objp = np.zeros((nx * ny, 3), np.float32)
    objp[:, :2] = np.mgrid[0:nx, 0:ny].T.reshape(-1, 2) * square_size
    objp[:, 0] -= (nx - 1) * square_size / 2
    objp[:, 1] -= (ny - 1) * square_size / 2
    return objp

def calibrate_camera(rgb, objp, nx, ny, K, dist):
    gray = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
    ret, corners = cv2.findChessboardCornersSB(gray, (nx, ny), None)
    if not ret:
        return None
    corners2 = cv2.cornerSubPix(
        gray, corners, (11, 11), (-1, -1),
        (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
    )
    success, rvec, tvec = cv2.solvePnP(objp, corners2, K, dist)
    if not success:
        return None
    R, _ = cv2.Rodrigues(rvec)
    T = np.eye(4); T[:3, :3] = R; T[:3, 3] = tvec.squeeze()
    proj_pts, _ = cv2.projectPoints(objp, rvec, tvec, K, dist)
    err = cv2.norm(corners2, proj_pts, cv2.NORM_L2) / len(proj_pts)
    return {'rvec': rvec, 'tvec': tvec, 'T': T, 'error': err}

def detect_pattern(rgb, nx, ny):
    gray = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
    ret, _ = cv2.findChessboardCornersSB(gray, (nx, ny), None)
    return bool(ret)

def extract_angles(rvec):
    R, _ = cv2.Rodrigues(rvec)
    e_y = R[:, 1]
    alpha = np.degrees(np.arctan2(e_y[0], e_y[1]))
    beta  = np.degrees(np.arctan2(e_y[2], e_y[1]))
    if alpha > 90: alpha -= 180
    elif alpha < -90: alpha += 180
    if beta > 90: beta -= 180
    elif beta < -90: beta += 180
    return alpha, beta

class AngleEstimatorNode(Node):
    def __init__(self):
        super().__init__('angle_estimator')
        self.bridge = CvBridge()

        pkg_path = get_package_share_directory('ur5e_env_description')
        default_calib_path = os.path.join(pkg_path, 'config', 'calib.npz')

        self.declare_parameter('calib_file', default_calib_path)
        self.declare_parameter('nx', 5)
        self.declare_parameter('ny', 21)
        self.declare_parameter('square_size', 0.007)
        self.declare_parameter('width', 0.042)
        self.declare_parameter('height', 0.077)

        data = np.load(self.get_parameter('calib_file').get_parameter_value().string_value)
        self.K, self.dist = data['K'], data['dist']

        self.ref_com = None

        self.angle_pub   = self.create_publisher(Float32MultiArray, 'angles', 10)
        self.disp_pub    = self.create_publisher(Float32MultiArray, 'displacements', 10)
        self.pattern_pub = self.create_publisher(Bool, 'pattern_detected', 10)

        # ⛑️ IMPORTANTE: guardar subs e sync em self + usar QoS sensor_data (BEST_EFFORT)
        self.rgb_sub   = Subscriber(self, Image, '/camera/color/image_raw',  qos_profile=qos_profile_sensor_data)
        self.depth_sub = Subscriber(self, Image, '/camera/depth/image_raw', qos_profile=qos_profile_sensor_data)
        self.sync = ApproximateTimeSynchronizer([self.rgb_sub, self.depth_sub], queue_size=10, slop=0.03)
        self.sync.registerCallback(self.process_frame)

        self.nx = self.get_parameter('nx').get_parameter_value().integer_value
        self.ny = self.get_parameter('ny').get_parameter_value().integer_value
        self.size   = self.get_parameter('square_size').get_parameter_value().double_value
        self.width  = self.get_parameter('width').get_parameter_value().double_value
        self.height = self.get_parameter('height').get_parameter_value().double_value

        self.get_logger().info("vision: subscrita a /camera/* (sensor_data). A aguardar frames...")

    def process_frame(self, rgb_msg, depth_msg):
        try:
            rgb   = self.bridge.imgmsg_to_cv2(rgb_msg, 'rgb8')
            depth = self.bridge.imgmsg_to_cv2(depth_msg, '32FC1')
        except CvBridgeError as e:
            self.get_logger().error(f'CvBridge falhou: {e}')
            return

        objp = build_objp(self.nx, self.ny, self.size)
        pose = calibrate_camera(rgb, objp, self.nx, self.ny, self.K, self.dist)
        if pose is None:
            self.pattern_pub.publish(Bool(data=False))
            self.disp_pub.publish(Float32MultiArray(data=[0.0, 0.0]))
            return

        self.get_logger().info(f'Erro reprojeção: {pose["error"]:.3f} px')
        rvec = pose['rvec']; tvec = pose['tvec'].squeeze()
        R, _ = cv2.Rodrigues(rvec)

        alpha, beta = extract_angles(rvec)
        self.angle_pub.publish(Float32MultiArray(data=[alpha, beta]))

        half_thickness = self.width / 2.0
        offset_cam = R.dot(np.array([0.0, 0.0, -half_thickness]))
        p_com_cam  = tvec + offset_cam

        if self.ref_com is None:
            self.ref_com = p_com_cam.copy()

        desc = p_com_cam - self.ref_com
        dx_off, dz_off = float(desc[0]), float(desc[2])
        self.disp_pub.publish(Float32MultiArray(data=[dx_off, dz_off]))

        ok = detect_pattern(rgb, self.nx, self.ny)
        self.pattern_pub.publish(Bool(data=ok))

def main():
    rclpy.init()
    node = AngleEstimatorNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
