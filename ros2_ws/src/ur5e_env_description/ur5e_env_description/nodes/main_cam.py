#!/usr/bin/env python3

import os
import time
import numpy as np
import mujoco, glfw
import OpenGL.GL as gl
import cv2
import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from sensor_msgs.msg import JointState
from ament_index_python.packages import get_package_share_directory
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

class MujocoSimulator(Node):
    def __init__(self):
        super().__init__('mujoco_simulator')

        pkg = get_package_share_directory('ur5e_env_description')
        xml_path = os.path.join(pkg, 'models', 'ur5e_env.xml')
        self.model = mujoco.MjModel.from_xml_path(xml_path)
        print("[DEBUG] model.nu (nº actuators):", self.model.nu)

        self.data = mujoco.MjData(self.model)
        self.actuated_dofs = self.model.nu

        self.qpos_home = self.data.qpos.copy()
        self.qpos_home[:6] = [0, -1.745, -2.27, 0.93, 1.53, 0.0]

        self.reset_simulation()

        if not glfw.init():
            raise RuntimeError("Falha ao inicializar GLFW")

        self.W, self.H = 1200, 900
        self.window = glfw.create_window(self.W, self.H, "Simulador UR5e + RealSense", None, None)

        if not self.window:
            glfw.terminate()
            raise RuntimeError("Falha ao criar a janela GLFW")
        glfw.make_context_current(self.window)

        self.reset = False
        glfw.set_key_callback(self.window, self._key_callback)
        

        self.vp_main = mujoco.MjrRect(0, 0, self.W, self.H)
        self.ctx_main = mujoco.MjrContext(self.model, mujoco.mjtFontScale.mjFONTSCALE_150.value)

        self.feed_w, self.feed_h = 1280, 720
        self.window_feed = glfw.create_window(self.feed_w, self.feed_h,"Feed RealSense Full-Res", None, self.window)

        self.ctx_feed_full = mujoco.MjrContext(self.model,mujoco.mjtFontScale.mjFONTSCALE_100.value)
        self.vp_feed_full = mujoco.MjrRect(0, 0, self.feed_w, self.feed_h)

        self.main_cam = mujoco.MjvCamera()
        self.main_cam.lookat = np.array([0.0, 0.0, 0.1])
        self.main_cam.distance = 2.5
        self.main_cam.azimuth = 45
        self.main_cam.elevation = -20

        cam_id = mujoco.mj_name2id(self.model, mujoco.mjtObj.mjOBJ_CAMERA, b"realsense")

        self.feed_cam = mujoco.MjvCamera()
        self.feed_cam.fixedcamid = cam_id
        self.feed_cam.type = mujoco.mjtCamera.mjCAMERA_FIXED

        self.opt = mujoco.MjvOption()
        self.scene = mujoco.MjvScene(self.model, maxgeom=1000)

        self.overlay_tex = gl.glGenTextures(1)
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
        gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, gl.GL_RGB, self.feed_w, self.feed_h, 0, gl.GL_RGB, gl.GL_UNSIGNED_BYTE, None)
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

        self.joint_name_to_idx = {}
        for i in range(self.model.njnt):
            name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, i)
            if name is not None:
                self.joint_name_to_idx[name] = i

        self.ignore_joint_updates = False


        self.create_subscription(JointTrajectory, '/ur5e_controller/joint_trajectory', self.cb_trajectory, 10)
        self.js_pub = self.create_publisher(JointState, '/joint_states', 10)
        self.create_service(Trigger, 'reset_simulation', self.cb_reset_service)

        self.bridge = CvBridge()
        self.rgb_pub   = self.create_publisher(Image, '/camera/color/image_raw', 10)
        self.depth_pub = self.create_publisher(Image, '/camera/depth/image_raw', 10)
        

    def _key_callback(self, window, key, scancode, action, mods):
        # quando pressiona Espaço
        if key == glfw.KEY_SPACE and action == glfw.PRESS:
            self.reset_simulation()

    def cb_trajectory(self, msg):
        if not msg.points:
            return
        pt: JointTrajectoryPoint = msg.points[-1]
        for name, pos in zip(msg.joint_names, pt.positions):
            if name in self.joint_name_to_idx:
                idx = self.joint_name_to_idx[name]
                if idx < self.actuated_dofs:
                    self.data.ctrl[idx] = pos

        self.get_logger().info(f"=== Trajectory received ===")
        self.get_logger().info(f"  joints: {msg.joint_names}")
        self.get_logger().info(f"  #points: {len(msg.points)}")
        for i, pt in enumerate(msg.points):
            self.get_logger().info(
                f"  pt[{i}]: pos={pt.positions}  vel={pt.velocities}  tfs=({pt.time_from_start.sec},"
                f"{pt.time_from_start.nanosec})"
            )

    def reset_simulation(self):
        self.ignore_joint_updates = True
        self.data.qpos[:] = self.qpos_home.copy()
        self.data.qvel[:] = 0.0
        self.data.ctrl[:6] = self.qpos_home[:6]
        mujoco.mj_forward(self.model, self.data)
        print("[INFO] Reset aplicado. A ignorar comandos por 0.5s...")
        print("[DEBUG] qpos:", self.data.qpos[:])
        print("[DEBUG] ctrl:", self.data.ctrl[:])

    def cb_reset_service(self, request, response):
        self.reset_simulation()
        response.success = True
        response.message = "Reset aplicado com sucesso via serviço."
        return response

    def update_overlay_texture(self, rgb_img):
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexSubImage2D(gl.GL_TEXTURE_2D, 0, 0, 0, self.feed_w, self.feed_h, gl.GL_RGB, gl.GL_UNSIGNED_BYTE, rgb_img)
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

    def draw_overlay(self, x, y, w, h):
        gl.glMatrixMode(gl.GL_PROJECTION)
        gl.glPushMatrix()
        gl.glLoadIdentity()
        gl.glOrtho(0, self.W, 0, self.H, -1, 1)
        gl.glMatrixMode(gl.GL_MODELVIEW)
        gl.glPushMatrix()
        gl.glLoadIdentity()

        gl.glEnable(gl.GL_TEXTURE_2D)
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glColor3f(1, 1, 1)
        gl.glBegin(gl.GL_QUADS)
        gl.glTexCoord2f(0, 0); gl.glVertex2f(x, y)
        gl.glTexCoord2f(1, 0); gl.glVertex2f(x+w, y)
        gl.glTexCoord2f(1, 1); gl.glVertex2f(x+w, y+h)
        gl.glTexCoord2f(0, 1); gl.glVertex2f(x, y+h)
        gl.glEnd()
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)
        gl.glDisable(gl.GL_TEXTURE_2D)

        gl.glPopMatrix()
        gl.glMatrixMode(gl.GL_PROJECTION)
        gl.glPopMatrix()
        gl.glMatrixMode(gl.GL_MODELVIEW)


    def step(self):
        # 1) avanço da simulação (primeira metade)
        mujoco.mj_step1(self.model, self.data)

        # 2) render principal (janela grande)
        mujoco.mjv_updateCamera(
            self.model, self.data, self.main_cam, self.scene
        )
        mujoco.mjv_updateScene(
            self.model, self.data, self.opt, None,
            self.main_cam, mujoco.mjtCatBit.mjCAT_ALL, self.scene
        )
        gl.glClearColor(0.1, 0.1, 0.1, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        mujoco.mjr_render(self.vp_main, self.scene, self.ctx_main)

        # 3) render do feed full-res na janela dedicada
        glfw.make_context_current(self.window_feed)
        mujoco.mjv_updateCamera(
            self.model, self.data, self.feed_cam, self.scene
        )
        mujoco.mjv_updateScene(
            self.model, self.data, self.opt, None,
            self.feed_cam, mujoco.mjtCatBit.mjCAT_ALL, self.scene
        )
        gl.glClearColor(0, 0, 0, 1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        mujoco.mjr_render(
            self.vp_feed_full, self.scene, self.ctx_feed_full
        )
        glfw.swap_buffers(self.window_feed)

        rgb_arr   = np.zeros((self.feed_h, self.feed_w, 3), dtype=np.uint8)
        depth_arr = np.zeros((self.feed_h, self.feed_w),   dtype=np.float32)
        mujoco.mjr_readPixels(rgb_arr, depth_arr,
                            self.vp_feed_full, self.ctx_feed_full)

        # corrige o flip vertical que o MuJoCo devolve
        rgb_arr   = np.flipud(rgb_arr)
        depth_arr = np.flipud(depth_arr)

        # converte para ROS Image msg e publica
        stamp = self.get_clock().now().to_msg()
        rgb_msg   = self.bridge.cv2_to_imgmsg(rgb_arr,   encoding='rgb8')
        depth_msg = self.bridge.cv2_to_imgmsg(depth_arr, encoding='32FC1')
        rgb_msg.header.stamp      = depth_msg.header.stamp = stamp
        rgb_msg.header.frame_id   = 'camera_color_optical_frame'
        depth_msg.header.frame_id = 'camera_depth_optical_frame'
        self.rgb_pub.publish(rgb_msg)
        self.depth_pub.publish(depth_msg)

        # 4) volta ao contexto da janela principal
        glfw.make_context_current(self.window)

        # 5) resto do step: publica joint-states e finaliza frame
        stamp = self.get_clock().now().to_msg()
        js = JointState()
        js.header.stamp = stamp
        js.name     = list(self.joint_name_to_idx.keys())[:6]
        js.position = self.data.qpos[:6].tolist()
        js.velocity = self.data.qvel[:6].tolist()
        js.effort   = self.data.qfrc_applied[:6].tolist()
        self.js_pub.publish(js)

        # 6) terminar frame da simulação
        mujoco.mj_step2(self.model, self.data)

        # 7) swap + poll na janela principal
        glfw.swap_buffers(self.window)
        glfw.poll_events()


    def run(self):
        print("[INFO] Simulação iniciada.")
        while not glfw.window_should_close(self.window) and rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.0)
            self.step()
            time.sleep(1/240.0)
        glfw.terminate()
        print("[INFO] Simulação terminada.")

def main():
    rclpy.init()
    node = MujocoSimulator()
    try:
        node.run()
    finally:
        rclpy.shutdown()

if __name__ == '__main__':
    main()
