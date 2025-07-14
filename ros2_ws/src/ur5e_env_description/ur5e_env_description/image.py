import numpy as np
import cv2

def extract_angles(rvec):
    R, _ = cv2.Rodrigues(rvec)
    e_y   = R[:,1]
    alpha = np.degrees(np.arctan2(e_y[0], e_y[1]))
    beta  = np.degrees(np.arctan2(e_y[2], e_y[1]))
    # normalizar [-90,90]
    if   alpha >  90: alpha -= 180
    elif alpha < -90: alpha += 180
    if   beta  >  90: beta  -= 180
    elif beta  < -90: beta  += 180
    return alpha, beta

# testa várias rotações puras
tests = [
    ('roll  20° X-axis', np.array([np.deg2rad(20), 0, 0])),  # X = esquerda–direita
    ('pitch 15° Z-axis', np.array([0, 0, np.deg2rad(15)])),  # Z = frente–trás
]

for name, (rx, ry, rz) in tests:
    # constrói matriz de rotação R = Rz * Ry * Rx (se for essa a convenção)
    Rx = np.array([[1,0,0],
                   [0,np.cos(rx),-np.sin(rx)],
                   [0,np.sin(rx), np.cos(rx)]])
    Rz = np.array([[ np.cos(rz),-np.sin(rz),0],
                   [ np.sin(rz), np.cos(rz),0],
                   [0,0,1]])
    R  = Rz @ Rx
    # obtém rvec
    rvec, _ = cv2.Rodrigues(R)
    alpha, beta = extract_angles(rvec)
    print(f"{name:20s} → α = {alpha:6.2f}°, β = {beta:6.2f}°")
