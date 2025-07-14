#!/usr/bin/env python3
import mujoco
import glfw
import OpenGL.GL as gl
import numpy as np
import time
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import os
from ament_index_python.packages import get_package_share_directory


class MuJoCoWithCam(Node):
    def __init__(self):
        super().__init__('mujoco_ros')
        # ROS subscriber
        self.joint_map = {}
        self.create_subscription(JointState, '/cmd_joints', self.cb_joints, 10)

        # GLFW e janela
        if not glfw.init():
            raise RuntimeError("Falha ao inicializar GLFW")
        self.window_width, self.window_height = 1200, 900
        self.window = glfw.create_window(self.window_width, self.window_height,
                                         "Ambiente com Overlay", None, None)
        if not self.window:
            glfw.terminate()
            raise RuntimeError("Falha ao criar janela GLFW")
        glfw.make_context_current(self.window)

        # Modelo e dados MuJoCo

        pkg_share = get_package_share_directory('mujoco_ros')
        xml_path  = os.path.join(pkg_share, 'assets', 'ur5e_env.xml')

        self.model = mujoco.MjModel.from_xml_path(xml_path)
        self.data  = mujoco.MjData(self.model)

        # Render contexts
        self.ctx_main = mujoco.MjrContext(self.model, 0)
        self.main_viewport = mujoco.MjrRect(0, 0,
                                            self.window_width,
                                            self.window_height)
        # Offscreen feed
        self.feed_w, self.feed_h = 340, 260
        self.ctx_feed     = mujoco.MjrContext(self.model, 0)
        self.feed_viewport = mujoco.MjrRect(800, 600,
                                            self.feed_w,
                                            self.feed_h)

        # após criar self.model e self.data
        self.joint_map = {}
        for jid in range(self.model.njnt):
            name = mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, jid)
            self.joint_map[name] = jid


        # Câmeras
        cam_id = mujoco.mj_name2id(self.model,
                    mujoco.mjtObj.mjOBJ_CAMERA, b"realsense")
        if cam_id < 0:
            raise RuntimeError("Câmera 'realsense' não encontrada")
        self.feed_cam = mujoco.MjvCamera()
        self.feed_cam.fixedcamid = cam_id
        self.feed_cam.type = mujoco.mjtCamera.mjCAMERA_FIXED

        self.main_cam = mujoco.MjvCamera()
        self.main_cam.lookat    = np.array([0.0,0.0,0.1])
        self.main_cam.distance  = 2.5
        self.main_cam.azimuth   = 45
        self.main_cam.elevation = -20

        self.opt   = mujoco.MjvOption()
        self.scene = mujoco.MjvScene(self.model, maxgeom=1000)

        # overlay texture
        self.overlay_tex = gl.glGenTextures(1)
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexParameteri(gl.GL_TEXTURE_2D,
                           gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D,
                           gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
        gl.glTexParameteri(gl.GL_TEXTURE_2D,
                           gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
        gl.glTexParameteri(gl.GL_TEXTURE_2D,
                           gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
        # allocate empty RGB
        gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, gl.GL_RGB,
                        self.feed_w, self.feed_h, 0,
                        gl.GL_RGB, gl.GL_UNSIGNED_BYTE, None)
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

    def cb_joints(self, msg: JointState):
        for name, pos in zip(msg.name, msg.position):
            if name in self.joint_map:
                idx = self.joint_map[name]
                self.data.qpos[idx] = pos
        # opcional: zerar velocidades
        self.data.qvel[:] = 0.0


    def update_overlay_texture(self, rgb_img):
        gl.glBindTexture(gl.GL_TEXTURE_2D, self.overlay_tex)
        gl.glTexSubImage2D(gl.GL_TEXTURE_2D, 0, 0, 0,
                           self.feed_w, self.feed_h,
                           gl.GL_RGB, gl.GL_UNSIGNED_BYTE, rgb_img)
        gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

    def draw_overlay(self, x, y):
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

    def run(self):
        while rclpy.ok() and not glfw.window_should_close(self.window):
            rclpy.spin_once(self, timeout_sec=0.0)
            mujoco.mj_step(self.model, self.data)

            # main view
            mujoco.mjv_updateCamera(self.model, self.data,
                                   self.main_cam, self.scene)
            mujoco.mjv_updateScene(self.model, self.data,
                                   self.opt, None,
                                   self.main_cam,
                                   mujoco.mjtCatBit.mjCAT_ALL,
                                   self.scene)
            gl.glClearColor(0.1,0.1,0.1,1)
            gl.glClear(gl.GL_COLOR_BUFFER_BIT
                       | gl.GL_DEPTH_BUFFER_BIT)
            mujoco.mjr_render(self.main_viewport,
                              self.scene, self.ctx_main)

            # offscreen feed
            mujoco.mjv_updateCamera(self.model, self.data,
                                   self.feed_cam, self.scene)
            mujoco.mjv_updateScene(self.model, self.data,
                                   self.opt, None,
                                   self.feed_cam,
                                   mujoco.mjtCatBit.mjCAT_ALL,
                                   self.scene)
            mujoco.mjr_render(self.feed_viewport,
                              self.scene, self.ctx_feed)
            gl.glFinish()

            # read pixels
            img = np.empty((self.feed_h,
                            self.feed_w, 4),
                            dtype=np.uint8)
            depth = np.empty((self.feed_h,
                              self.feed_w),
                              dtype=np.float32)
            mujoco.mjr_readPixels(img, depth,
                                  self.feed_viewport,
                                  self.ctx_feed)
            img = np.flipud(img)
            rgb = img[:,:,:3]

            self.update_overlay_texture(rgb)
            self.draw_overlay(50,
                              self.window_height
                              - self.feed_h
                              - 50)

            glfw.swap_buffers(self.window)
            glfw.poll_events()
            time.sleep(0.01)

        glfw.terminate()

def main(args=None):
    rclpy.init(args=args)
    node = MuJoCoWithCam()
    try:
        node.run()
    except KeyboardInterrupt:
        pass
    rclpy.shutdown()

if __name__ == '__main__':
    main()
