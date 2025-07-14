#!/usr/bin/env python3
import os
import time
import numpy as np
import mujoco, glfw
import OpenGL.GL as gl
import cv2

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from ament_index_python.packages import get_package_share_directory

class RealsenseFeed(Node):
    def __init__(self):
        super().__init__('mujoco_feed')
        # carrega MJCF
        pkg = get_package_share_directory('mujoco_ros')
        xml = os.path.join(pkg, 'assets', 'ur5e_env.xml')
        self.model = mujoco.MjModel.from_xml_path(xml)
        self.data  = mujoco.MjData(self.model)
        
        # Guarda a imagem mais recente
        self.current_image = None
        self.current_depth = None
        self.current_rgbd = None

        # mapeamento nome → índice em qpos
        self.joint_map = {
            mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, i): i
            for i in range(self.model.njnt)
        }

        # subscribe ao joint_states
        self.create_subscription(JointState, '/joint_states', self.cb_js, 10)

        # inicializa janela OffScreen feed
        if not glfw.init():
            raise RuntimeError("GLFW init falhou")
        W, H = 340, 260
        self.win = glfw.create_window(W, H, "Realsense Feed", None, None)
        glfw.make_context_current(self.win)
        self.ctx = mujoco.MjrContext(self.model, 0)
        self.vp  = mujoco.MjrRect(0, 0, W, H)

        # configura câmera fixa no corpo
        cam_id = mujoco.mj_name2id(self.model, mujoco.mjtObj.mjOBJ_CAMERA, b"realsense")
        if cam_id < 0:
            raise RuntimeError("Câmera 'realsense' não encontrada")
        self.cam = mujoco.MjvCamera()
        self.cam.fixedcamid = cam_id
        self.cam.type       = mujoco.mjtCamera.mjCAMERA_FIXED

        self.opt   = mujoco.MjvOption()
        self.scene = mujoco.MjvScene(self.model, maxgeom=1000)


    def cb_js(self, msg: JointState):
        # sempre que recebe joint_states, atualiza data.qpos
        for name, pos in zip(msg.name, msg.position):
            if name in self.joint_map:
                idx = self.joint_map[name]
                self.data.qpos[idx] = pos
        # opcional: zera velocidades
        self.data.qvel[:] = 0.0

    def spin(self):
        rate = 1/240.0
        while rclpy.ok() and not glfw.window_should_close(self.win):
            # processa callback ROS
            rclpy.spin_once(self, timeout_sec=0.0)
            # simula um passo (com data.qpos já atualizado)
            mujoco.mj_step(self.model, self.data)

            # render off-screen feed
            mujoco.mjv_updateCamera(self.model, self.data,
                                   self.cam, self.scene)
            mujoco.mjv_updateScene(self.model, self.data,
                                   self.opt, None,
                                   self.cam,
                                   mujoco.mjtCatBit.mjCAT_ALL,
                                   self.scene)
            gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
            mujoco.mjr_render(self.vp, self.scene, self.ctx)

            # Captura de imagem RGBD
            rgb = np.zeros((self.vp.height, self.vp.width, 3), dtype=np.uint8)
            depth = np.zeros((self.vp.height, self.vp.width), dtype=np.float32)

            mujoco.mjr_readPixels(rgb, depth, self.vp, self.ctx)

            # Inverter verticalmente (MuJoCo guarda de baixo para cima)
            rgb = np.flipud(rgb)
            depth = np.flipud(depth)

            self.current_image = rgb
            self.current_depth = depth

            # Guardar uma imagem apenas uma vez
            # Detetar se o utilizador clicou na tecla 'S'
            if glfw.get_key(self.win, glfw.KEY_S) == glfw.PRESS:

                timestamp = int(time.time())  # para nomear ficheiros únicos

                # Normalizar a depth para 0–255
                depth_norm = np.nan_to_num(depth, nan=0.0, posinf=0.0)
                depth_norm = (depth_norm - depth_norm.min()) / (depth_norm.max() - depth_norm.min() + 1e-8)
                depth_uint8 = (depth_norm * 255).astype(np.uint8)
                depth_uint8 = depth_uint8[:, :, np.newaxis]

                # Concatenar RGB + Depth
                rgbd = np.concatenate((rgb, depth_uint8), axis=2)
                self.current_rgbd = rgbd

                # Guardar ficheiros com timestamp
                cv2.imwrite(f"/tmp/rgb_{timestamp}.png", rgb)
                cv2.imwrite(f"/tmp/depth_{timestamp}.png", depth_uint8)
                cv2.imwrite(f"/tmp/rgbd_{timestamp}.png", rgbd[:, :, :3])  # visualização RGB

                print(f"[INFO] Imagem RGBD guardada com timestamp {timestamp}")


            glfw.swap_buffers(self.win)
            glfw.poll_events()
            time.sleep(rate)
        glfw.terminate()

def get_current_image(self):
    return self.current_image

def get_current_depth(self):
    return self.current_depth

def get_current_rgbd(self):
    return self.current_rgbd


def main():
    rclpy.init()
    node = RealsenseFeed()
    try:
        node.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
