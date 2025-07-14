#!/usr/bin/env python3
import os
import time
import numpy as np
import mujoco
import glfw
import OpenGL.GL as gl

import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from sensor_msgs.msg import JointState
from ament_index_python.packages import get_package_share_directory


class MuJoCoRLBridge(Node):
    def __init__(self, xml_path: str, gui: bool = True, window_size=(1200, 900)):
        super().__init__('mujoco_rl_bridge')

        # 1) resolve XML path
        if not os.path.isabs(xml_path):
            pkg_share = get_package_share_directory('mujoco_ros')
            xml_path = os.path.join(pkg_share, 'assets', xml_path)
        self.get_logger().info(f"Using MJCF at: {xml_path}")

        # 2) MuJoCo init
        self.model = mujoco.MjModel.from_xml_path(xml_path)
        self.data  = mujoco.MjData(self.model)
        self.gui   = gui

        # 3) GLFW window + main context
        if self.gui:
            if not glfw.init():
                raise RuntimeError("Failed to initialize GLFW")
            w, h = window_size
            self.window_width, self.window_height = w, h
            self.window = glfw.create_window(w, h, "MuJoCo RL Bridge", None, None)
            if not self.window:
                glfw.terminate()
                raise RuntimeError("Failed to create GLFW window")
            glfw.make_context_current(self.window)
            self.ctx_main      = mujoco.MjrContext(self.model, 0)
            self.viewport_main = mujoco.MjrRect(0, 0, w, h)

        # 4) UR5e joints + map name→qpos index
        self.joint_names = [
            'shoulder_pan_joint', 'shoulder_lift_joint', 'elbow_joint',
            'wrist_1_joint', 'wrist_2_joint', 'wrist_3_joint'
        ]
        self.joint_map = {
            name: mujoco.mj_name2id(
                self.model, mujoco.mjtObj.mjOBJ_JOINT, name.encode()
            )
            for name in self.joint_names
        }

        # 5) ROS publishers & subscribers
        self.pub_js   = self.create_publisher(JointState, '/joint_states', 10)
        self.sub_cmd  = self.create_subscription(
            JointState, '/cmd_joints', self.cb_cmdj, 10
        )
        self.pub_traj = self.create_publisher(
            JointTrajectory,
            '/joint_trajectory_controller/command',
            10
        )

        # --- A PARTIR DAQUI, código do feed da RealSense --------------

        # 6) cria contexto offscreen e viewport para o feed
        self.feed_w, self.feed_h = 340, 260
        if self.gui:
            self.ctx_feed      = mujoco.MjrContext(self.model, 0)
            # posiciona no canto superior direito, 10px margem
            x0 = window_size[0] - self.feed_w - 10
            y0 = window_size[1] - self.feed_h - 10
            self.feed_viewport = mujoco.MjrRect(x0, y0, self.feed_w, self.feed_h)

        # 7) inicializa a câmera "realsense" do XML
        cam_id = mujoco.mj_name2id(
            self.model, mujoco.mjtObj.mjOBJ_CAMERA, b"realsense"
        )
        if cam_id < 0:
            raise RuntimeError("Camera 'realsense' not found in model")
        self.feed_cam = mujoco.MjvCamera()
        self.feed_cam.fixedcamid = cam_id
        self.feed_cam.type       = mujoco.mjtCamera.mjCAMERA_FIXED

        # 8) configura main_cam para visão global
        self.main_cam = mujoco.MjvCamera()
        self.main_cam.lookat    = np.array([0.0, 0.0, 0.1])
        self.main_cam.distance  = 2.5
        self.main_cam.azimuth   = 45
        self.main_cam.elevation = -20

        # 9) cena e opções de render
        self.opt   = mujoco.MjvOption()
        self.scene = mujoco.MjvScene(self.model, maxgeom=1000)

        # 10) cria textura OpenGL vazia para o overlay do feed
        self.overlay_tex = gl.glGenTextures(1)
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
        gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
        gl.glTexImage2D(
            gl.GL_TEXTURE_2D, 0, gl.GL_RGB,
            self.feed_w, self.feed_h, 0,
            gl.GL_RGB, gl.GL_UNSIGNED_BYTE, None
        )
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

    def cb_cmdj(self, msg: JointState):
        """Converte JointState em JointTrajectory de 1 ponto e publica."""
        traj = JointTrajectory()
        traj.joint_names = self.joint_names

        pt = JointTrajectoryPoint()
        desired = [0.0]*len(self.joint_names)
        for name, pos in zip(msg.name, msg.position):
            if name in self.joint_map:
                idx = self.joint_names.index(name)
                desired[idx] = pos
        pt.positions = desired
        pt.time_from_start.sec = 1
        traj.points = [pt]
        self.pub_traj.publish(traj)

    def _publish_joint_states(self):
        js = JointState()
        js.header.stamp = self.get_clock().now().to_msg()
        js.name     = self.joint_names
        js.position = [
            float(self.data.qpos[self.joint_map[j]])
            for j in self.joint_names
        ]
        self.pub_js.publish(js)

    def _update_overlay(self, rgb_img):
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexSubImage2D(
            gl.GL_TEXTURE_2D, 0, 0, 0,
            self.feed_w, self.feed_h,
            gl.GL_RGB, gl.GL_UNSIGNED_BYTE, rgb_img
        )
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

    def _draw_overlay(self):
        x = self.feed_viewport.left
        y = self.feed_viewport.bottom
        w, h = self.feed_w, self.feed_h
        # set ortho
        gl.glMatrixMode(gl.GL_PROJECTION)
        gl.glPushMatrix(); gl.glLoadIdentity()
        gl.glOrtho(0, self.window_width, 0, self.window_height, -1, 1)
        gl.glMatrixMode(gl.GL_MODELVIEW)
        gl.glPushMatrix(); gl.glLoadIdentity()
        # draw quad
        gl.glEnable(gl.GL_TEXTURE_2D)
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
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
        # 1) ROS callbacks
        rclpy.spin_once(self, timeout_sec=0.0)
        # 2) MuJoCo step
        mujoco.mj_step(self.model, self.data)
        # 3) publica joint_states
        self._publish_joint_states()

        if not self.gui:
            return

        # 4) render principal
        mujoco.mjv_updateCamera(
            self.model, self.data,
            self.main_cam, self.scene
        )
        mujoco.mjv_updateScene(
            self.model, self.data,
            self.opt, None,
            self.main_cam,
            mujoco.mjtCatBit.mjCAT_ALL,
            self.scene
        )
        gl.glClearColor(0.1,0.1,0.1,1)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
        mujoco.mjr_render(self.viewport_main, self.scene, self.ctx_main)

        # 5) render offscreen feed
        mujoco.mjv_updateCamera(
            self.model, self.data,
            self.feed_cam, self.scene
        )
        mujoco.mjv_updateScene(
            self.model, self.data,
            self.opt, None,
            self.feed_cam,
            mujoco.mjtCatBit.mjCAT_ALL,
            self.scene
        )
        mujoco.mjr_render(self.feed_viewport, self.scene, self.ctx_feed)
        gl.glFinish()

        # 6) ler pixels e sobrepor
        img   = np.empty((self.feed_h, self.feed_w, 4), dtype=np.uint8)
        depth = np.empty((self.feed_h, self.feed_w),   dtype=np.float32)
        mujoco.mjr_readPixels(img, depth,
                              self.feed_viewport, self.ctx_feed)
        img = np.flipud(img)
        self._update_overlay(img[:,:,:3])
        self._draw_overlay()

        glfw.swap_buffers(self.window)
        glfw.poll_events()

    def run(self):
        while rclpy.ok() and (not glfw.window_should_close(self.window) if self.gui else True):
            self.step()
            time.sleep(1/240.0)
        if self.gui:
            glfw.terminate()


def main():
    rclpy.init()
    bridge = MuJoCoRLBridge(xml_path='ur5e_env.xml', gui=True)
    try:
        bridge.run()
    except KeyboardInterrupt:
        pass
    finally:
        bridge.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
