import numpy as np
import cv2 as cv

def euler_to_rotation_matrix(roll, pitch, yaw):
    """Converte ângulos em graus para matriz de rotação 3x3 (ordem: XYZ)"""
    r = np.deg2rad(roll)
    p = np.deg2rad(pitch)
    y = np.deg2rad(yaw)

    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(r), -np.sin(r)],
        [0, np.sin(r),  np.cos(r)]
    ])
    Ry = np.array([
        [ np.cos(p), 0, np.sin(p)],
        [0, 1, 0],
        [-np.sin(p), 0, np.cos(p)]
    ])
    Rz = np.array([
        [np.cos(y), -np.sin(y), 0],
        [np.sin(y),  np.cos(y), 0],
        [0, 0, 1]
    ])

    return Rz @ Ry @ Rx  # ordem: roll → pitch → yaw (X → Y → Z)


def showObject(img, roll, pitch, yaw, distance, K, dist, color=(0, 255, 0), thickness=2):
    """
    Desenha um paralelepípedo 3D projetado em 2D com rotação (graus) e translação Z.
    """
    L, H, D = 0.042, 0.154, 0.042  # dimensões do paralelepípedo (m)
   
    # Vértices centrados na origem (centro de massa)
    vertices = np.array([
        [+L/2, -H/2, -D/2],  # 0
        [-L/2, -H/2, -D/2],  # 1
        [+L/2, +H/2, -D/2],  # 2
        [-L/2, +H/2, -D/2],  # 3
        [+L/2, -H/2, +D/2],  # 4
        [-L/2, -H/2, +D/2],  # 5
        [+L/2, +H/2, +D/2],  # 6
        [-L/2, +H/2, +D/2],  # 7
    ], dtype=np.float32)

    # Rotação aplicada
    R = euler_to_rotation_matrix(roll, pitch, yaw)
    rotated = vertices @ R.T

    # Translação em Z (simula distância à câmara)
    translated = rotated + np.array([[0, 0, distance]])

    # Projeção
    rvec = np.zeros((3, 1))  # sem rotação da câmara
    tvec = np.zeros((3, 1))
    tvec_corrigido = tvec + np.array([[0],[0],[D/2]])
    image_points, _ = cv.projectPoints(translated, rvec, tvec_corrigido, K, dist)

    # Arestas (12 ligações)
    edges = [
        (0, 1), (1, 3), (3, 2), (2, 0),  # frente
        (4, 5), (5, 7), (7, 6), (6, 4),  # trás
        (0, 4), (1, 5), (2, 6), (3, 7)   # ligações
    ]
    for i, j in edges:
        pt1 = tuple(image_points[i].ravel().astype(int))
        pt2 = tuple(image_points[j].ravel().astype(int))
        cv.line(img, pt1, pt2, color, thickness)

    # Pontos numerados (opcional)
    for i, pt in enumerate(image_points):
        x, y = pt.ravel()
        cv.circle(img, (int(x), int(y)), 3, (0, 255, 255), -1)
        cv.putText(img, str(i), (int(x)+4, int(y)-4), cv.FONT_HERSHEY_SIMPLEX, 0.4, (0,255,255), 1)

    return img


L, H, D = 0.042, 0.154, 0.042      # Largura, Altura, Profundidade

# Gerar 8 vértices centrados em (0, 0, 0)
vertices = np.array([
    [+L/2, -H/2, -D/2],  # 0: canto inferior esquerdo da frente
    [-L/2, -H/2, -D/2],  # 1: canto inferior direito da frente
    [+L/2, +H/2, -D/2],  # 2: canto superior direito da frente
    [-L/2, +H/2, -D/2],  # 3: canto superior esquerdo da frente
    [+L/2, -H/2, +D/2],  # 4: canto inferior direito de trás
    [-L/2, -H/2, +D/2],  # 5: canto inferior esquerdo de trás
    [+L/2, +H/2, +D/2],  # 6: canto superior direito de trás
    [-L/2, +H/2, +D/2],  # 7: canto superior esquerdo de trás
], dtype=np.float32)


# Carregar intrinsecos e extrinsecos

calib = np.load('camera_calibration.npz')
K = calib['K']
dist = calib['dist']

pose = np.load('camera_to_object.npz')
rvec = pose['rvec']
tvec = pose['tvec']

# Projetar os vértices na imagem
image_points, jacobian = cv.projectPoints(vertices, rvec, tvec, K, dist)

# Carregar a imagem
img = cv.imread('src/capturas_realsense/capture_000_color.png')

# Desenhar os vértices projetados na imagem 2D
for i, point in enumerate(image_points):
    u, v = point.ravel()
    center = (int(u), int(v))
    cv.circle(img, center, 5, (0, 0, 255), -1)
    cv.putText(img, f'{i}', (center[0]+5, center[1]-5), cv.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 255), 1)

# # Desenhar as 12 arestas do paralelepípedo
# edges = [
#     (0, 1), (1, 3), (3, 2), (2, 0),  # face frontal
#     (4, 5), (5, 7), (7, 6), (6, 4),  # face traseira
#     (0, 4), (1, 5), (2, 6), (3, 7)   # ligações entre faces
# ]

# for i, j in edges:
#     pt1 = tuple(image_points[i].ravel().astype(int))
#     pt2 = tuple(image_points[j].ravel().astype(int))
#     cv.line(img, pt1, pt2, (0, 255, 0), 2)  # verde

img = showObject(img, roll=0, pitch=0, yaw=-5, distance=0.27, K=K, dist=dist)
cv.imshow("Objeto Projetado", img)
cv.waitKey(0)
cv.destroyAllWindows()