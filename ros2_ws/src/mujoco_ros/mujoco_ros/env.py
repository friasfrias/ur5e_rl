import mujoco
from mujoco import viewer
import glfw
import OpenGL.GL as gl
import numpy as np
import cv2
import time
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState

# --- 1) Cria o Node ROS2 e subscrição a /cmd_joints ---
rclpy.init()
node = Node('mujoco_with_cam')

# vamos preencher isto no callback:
joint_map = {}
def cb_joints(msg: JointState):
    # atualiza data.qpos nos endereços correspondentes
    for name, pos in zip(msg.name, msg.position):
        if name in joint_map:
            addr = joint_map[name]
            data.qpos[addr] = pos
    # opcional: zera velocidades
    data.qvel[:] = 0.0

node.create_subscription(JointState, '/cmd_joints', cb_joints, 10)

# --- 1. Inicialização do GLFW e criação da janela principal ---
if not glfw.init():
    raise Exception("Falha ao inicializar GLFW")

# Define as dimensões da janela principal (ajusta conforme necessário)
window_width, window_height = 1200, 900
window = glfw.create_window(window_width, window_height, "Ambiente com Overlay do Feed", None, None)
if not window:
    glfw.terminate()
    raise Exception("Falha ao criar a janela GLFW")
glfw.make_context_current(window)

# --- 2. Carregar o modelo e os dados a partir do XML ---
# Certifica-te que o XML "assets/ur5e_env.xml" define o robô com a câmara "realsense"
xml_path = "assets/ur5e_env.xml"
model = mujoco.MjModel.from_xml_path(xml_path)
data = mujoco.MjData(model)

# --- 3. Criar os contextos de renderização ---
# Contexto para a janela principal (renderizando todo o ambiente)
ctx_main = mujoco.MjrContext(model, 0)  # device_id=0 utiliza a GPU
main_viewport = mujoco.MjrRect(0, 0, window_width, window_height)

# Contexto offscreen para renderizar o feed da câmara – definindo um viewport menor
feed_width, feed_height = 340, 260
ctx_feed = mujoco.MjrContext(model, 0)
feed_viewport = mujoco.MjrRect(800, 600, feed_width, feed_height)

# agora que temos model/data, podemos preencher joint_map:
for name in model.joint_names:
    joint_map[name] = model.joint_name2id(name)  # qpos index

# --- 4. Configuração das câmaras ---
# Obter o ID da câmera "realsense" definida no XML (passa o nome em bytes)
camera_id = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_CAMERA, b"realsense")
if camera_id < 0:
    raise ValueError("Câmera 'realsense' não encontrada no XML!")

# Configuração da câmera para o feed offscreen
feed_cam = mujoco.MjvCamera()
feed_cam.fixedcamid = camera_id
feed_cam.type = mujoco.mjtCamera.mjCAMERA_FIXED
# Se os parâmetros (posição, orientação) desejados já estão no XML, eles serão usados; se precisar de ajustes,
# podes modificá‑los aqui (por exemplo, feed_cam.lookat, feed_cam.distance, etc.).

# Configuração de uma câmera principal para a visualização global do ambiente
main_cam = mujoco.MjvCamera()
main_cam.lookat = np.array([0.0, 0.0, 0.1])  # Ajusta este vetor para centralizar o robô
main_cam.distance = 2.5
main_cam.azimuth = 45
main_cam.elevation = -20

# --- 5. Criar opções visuais e a cena ---
opt = mujoco.MjvOption()
scene = mujoco.MjvScene(model, maxgeom=1000)

# --- 6. Configurar a textura para o overlay do feed ---
overlay_tex = gl.glGenTextures(1)
gl.glBindTexture(gl.GL_TEXTURE_2D, overlay_tex)
gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_S, gl.GL_CLAMP_TO_EDGE)
gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_WRAP_T, gl.GL_CLAMP_TO_EDGE)
gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MAG_FILTER, gl.GL_LINEAR)
gl.glTexParameteri(gl.GL_TEXTURE_2D, gl.GL_TEXTURE_MIN_FILTER, gl.GL_LINEAR)
# Aloca uma textura vazia com formato RGB
gl.glTexImage2D(gl.GL_TEXTURE_2D, 0, gl.GL_RGB, feed_width, feed_height, 0,
                gl.GL_RGB, gl.GL_UNSIGNED_BYTE, None)
gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

def update_overlay_texture(rgb_img):
    """
    Atualiza a textura do overlay com a imagem feed (formato RGB).
    rgb_img: array com shape (feed_height, feed_width, 3) dtype=uint8.
    """
    gl.glBindTexture(gl.GL_TEXTURE_2D, overlay_tex)
    gl.glTexSubImage2D(gl.GL_TEXTURE_2D, 0, 0, 0, feed_width, feed_height,
                       gl.GL_RGB, gl.GL_UNSIGNED_BYTE, rgb_img)
    gl.glBindTexture(gl.GL_TEXTURE_2D, 0)

def draw_overlay(x, y, w, h):
    """
    Desenha o overlay da textura na posição (x, y) com dimensões (w, h).
    """
    gl.glMatrixMode(gl.GL_PROJECTION)
    gl.glPushMatrix()
    gl.glLoadIdentity()
    gl.glOrtho(0, window_width, 0, window_height, -1, 1)
    gl.glMatrixMode(gl.GL_MODELVIEW)
    gl.glPushMatrix()
    gl.glLoadIdentity()
    
    gl.glEnable(gl.GL_TEXTURE_2D)
    gl.glBindTexture(gl.GL_TEXTURE_2D, overlay_tex)
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

# --- 7. Loop principal de simulação e renderização ---
while not glfw.window_should_close(window) and rclpy.ok():
    # processa qualquer JointState
    rclpy.spin_once(node, timeout_sec=0.0)
    # Avança um passo na simulação
    mujoco.mj_step(model, data)
    
    # Renderização da cena principal (ambiente completo usando main_cam)
    mujoco.mjv_updateCamera(model, data, main_cam, scene)
    mujoco.mjv_updateScene(model, data, opt, None, main_cam,
                           mujoco.mjtCatBit.mjCAT_ALL, scene)
    gl.glClearColor(0.1, 0.1, 0.1, 1)
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
    mujoco.mjr_render(main_viewport, scene, ctx_main)
    
    # Renderização offscreen do feed da câmara (usando feed_cam)
    mujoco.mjv_updateCamera(model, data, feed_cam, scene)
    mujoco.mjv_updateScene(model, data, opt, None, feed_cam,
                           mujoco.mjtCatBit.mjCAT_ALL, scene)
    mujoco.mjr_render(feed_viewport, scene, ctx_feed)
    gl.glFinish()
    
    # Leitura dos pixels do feed offscreen
    feed_img = np.empty((feed_height, feed_width, 4), dtype=np.uint8)
    feed_depth = np.empty((feed_height, feed_width), dtype=np.float32)
    mujoco.mjr_readPixels(feed_img, feed_depth, feed_viewport, ctx_feed)
    # Aplica flip vertical para corrigir a orientação (se a imagem vier invertida)
    feed_img = np.flipud(feed_img)
    # Extrai os 3 canais (RGB) – ignoramos o alfa
    feed_rgb = feed_img[:, :, :3]
    
    # Atualiza a textura do overlay com o feed capturado
    update_overlay_texture(feed_rgb)
    
    # Define a posição do overlay na janela principal (por exemplo, canto superior esquerdo com 10px de margem)
    overlay_x = 50
    overlay_y = window_height - feed_height - 50
    draw_overlay(overlay_x, overlay_y, feed_width, feed_height)
    
    glfw.swap_buffers(window)
    glfw.poll_events()
    time.sleep(0.01)

glfw.terminate()
