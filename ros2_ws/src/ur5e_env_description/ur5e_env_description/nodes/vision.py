#!/usr/bin/env python3

import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Float32MultiArray
from cv_bridge import CvBridge, CvBridgeError
from message_filters import Subscriber, ApproximateTimeSynchronizer
from std_srvs.srv import Trigger

def build_objp(nx, ny, square_size):
    """
    Gera os pontos 3D do padrão de xadrez centrais na origem.
    """
    objp = np.zeros((nx * ny, 3), np.float32)
    objp[:, :2] = np.mgrid[0:nx, 0:ny].T.reshape(-1, 2) * square_size
    objp[:, 0] -= (nx - 1) * square_size / 2
    objp[:, 1] -= (ny - 1) * square_size / 2
    return objp


def calibrate_camera(rgb, objp, nx, ny, K, dist):
    """
    Deteta o padrão, faz solvePnP, devolve rvec, tvec, matriz T e reproj_error.
    """
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
    T = np.eye(4)
    T[:3, :3] = R
    T[:3, 3] = tvec.squeeze()
    proj_pts, _ = cv2.projectPoints(objp, rvec, tvec, K, dist)
    err = cv2.norm(corners2, proj_pts, cv2.NORM_L2) / len(proj_pts)
    return {'rvec': rvec, 'tvec': tvec, 'T': T, 'error': err}


def extract_angles(rvec):
    """
    Extrai os ângulos alpha e beta a partir da matriz R, em graus.
    """
    R, _ = cv2.Rodrigues(rvec)
    e_y = R[:, 1]
    alpha = np.degrees(np.arctan2(e_y[0], e_y[1]))
    beta = np.degrees(np.arctan2(e_y[2], e_y[1]))
    # normalizar [-90,90]
    if alpha > 90:
        alpha -= 180
    elif alpha < -90:
        alpha += 180
    if beta > 90:
        beta -= 180
    elif beta < -90:
        beta += 180
    return alpha, beta


class AngleEstimatorNode(Node):
    def __init__(self):
        super().__init__('angle_estimator')
        self.bridge = CvBridge()
        # Parâmetros
        calib_file = self.declare_parameter('calib_file', '').get_parameter_value().string_value
        nx         = self.declare_parameter('nx', 5).get_parameter_value().integer_value
        ny         = self.declare_parameter('ny', 21).get_parameter_value().integer_value
        size       = self.declare_parameter('square_size', 0.007).get_parameter_value().double_value
        width  = self.declare_parameter('width', 0.042).get_parameter_value().double_value
        height  = self.declare_parameter('height', 0.077).get_parameter_value().double_value

        # Carrega a calibração a partir do ficheiro
        data = np.load(calib_file)
        self.K, self.dist = data['K'], data['dist']

        # Guardar o centro de massa (COM) de referência
        self.ref_com = None

        # Publishers
        self.angle_pub = self.create_publisher(
            Float32MultiArray,
            'angles',
            10
        )
        self.disp_pub = self.create_publisher(
            Float32MultiArray,
            'displacements',
            10
        )

        # Subscrever e sincronizar RGB+Depth
        rgb_sub = Subscriber(self, Image, '/camera/color/image_raw')
        depth_sub = Subscriber(self, Image, '/camera/depth/image_raw')
        sync = ApproximateTimeSynchronizer(
            [rgb_sub, depth_sub],
            queue_size=10,
            slop=0.03
        )
        sync.registerCallback(self.process_frame)

        self.nx, self.ny, self.size, self.width, self.height = nx, ny, size, width, height

        
    def process_frame(self, rgb_msg, depth_msg):
        try:
            rgb = self.bridge.imgmsg_to_cv2(rgb_msg, 'rgb8')
            depth = self.bridge.imgmsg_to_cv2(depth_msg, '32FC1')
        except CvBridgeError as e:
            self.get_logger().error(f'CvBridge falhou: {e}')
            return

        # Construir pontos do tabuleiro
        nx = self.get_parameter('nx').get_parameter_value().integer_value
        ny = self.get_parameter('ny').get_parameter_value().integer_value
        size = self.get_parameter('square_size').get_parameter_value().double_value
        width = self.get_parameter('width').get_parameter_value().double_value
        height  = self.get_parameter('height').get_parameter_value().double_value
        objp = build_objp(nx, ny, size)

        # Estima pose
        pose = calibrate_camera(rgb, objp, nx, ny, self.K, self.dist)
        if pose is None:
            self.get_logger().warning('Falha na deteção do padrão ou solvePnP')
            # publica um comando neutro para parar o robô
            zero_disp = Float32MultiArray(data=[0.0, 0.0])
            self.disp_pub.publish(zero_disp)
            return
        self.get_logger().info(f'Erro reprojeção: {pose["error"]:.3f} px')

        rvec = pose['rvec']
        tvec = pose['tvec'].squeeze()
        R, _ = cv2.Rodrigues(rvec)

        # 2) Publishes angles for monitoring/debug
        alpha, beta = extract_angles(rvec)
        angle_msg = Float32MultiArray(data=[alpha, beta])
        self.angle_pub.publish(angle_msg)

        # 3) Computa offset do tabuleiro ao COM do bloco (meia-espessura atrás do tabuleiro)
        half_thickness = width / 2
        offset_local  = np.array([0.0, 0.0, -half_thickness])

        # 4) Transforma offset para espaço da câmara e soma ao tvec
        offset_cam  = R.dot(offset_local)    # (3,)
        p_com_cam   = tvec + offset_cam      # (3,)

        if self.ref_com is None:
            self.ref_com = p_com_cam.copy()

        # Cálculo dos deslocamentos em x e em x do centro de massa
        desc_com = p_com_cam - self.ref_com
        dx_off, dz_off = float(desc_com[0]), float(desc_com[2])

        # # Converter em deslocamentos (m)
        # alpha_rad = np.deg2rad(alpha)
        # beta_rad = np.deg2rad(beta)
        # dx_angle = (height/2) * np.tan(alpha_rad)
        # dz_angle = (height/2) * np.tan(beta_rad)
        
        # Publicar deslocamentos
        disp_msg = Float32MultiArray(data=[dx_off, dz_off])
        self.disp_pub.publish(disp_msg)

def main():
    rclpy.init()
    node = AngleEstimatorNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
