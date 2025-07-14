#!/usr/bin/env python3
import numpy as np
import cv2 as cv

def main():
    # --- Carregar calibração intrínseca ---
    calib = np.load('camera_calibration.npz')
    K    = calib['K']
    dist = calib['dist']

    # --- Carregar pose estimada pelo solvePnP (camera → objeto) ---
    pose = np.load('camera_to_object.npz')
    rvec = pose['rvec']  # 3x1
    tvec = pose['tvec']  # 3x1

    # --- Dimensões do paralelepípedo (m) ---
    L, H, D = 0.042, 0.154, 0.042

    # --- Definir os 8 vértices centrados em (0,0,0) no frame do objeto ---
    vertices = np.array([
        [+L/2, -H/2, -D/2],  # 0: inf-esq frente
        [-L/2, -H/2, -D/2],  # 1: inf-dir frente
        [+L/2, +H/2, -D/2],  # 2: sup-esq frente
        [-L/2, +H/2, -D/2],  # 3: sup-dir frente
        [+L/2, -H/2, +D/2],  # 4: inf-esq trás
        [-L/2, -H/2, +D/2],  # 5: inf-dir trás
        [+L/2, +H/2, +D/2],  # 6: sup-esq trás
        [-L/2, +H/2, +D/2],  # 7: sup-dir trás
    ], dtype=np.float32)

    # --- Converter rvec para matriz de rotação 3×3 ---
    R_obj, _ = cv.Rodrigues(rvec)

    # --- Ajustar tvec para colar a face frontal ao padrão (compensa D/2 no eixo Z do objeto) ---
    offset = R_obj @ np.array([[0], [0], [D/2]], dtype=np.float32)
    tvec_corr = tvec + offset

    # --- Projetar vértices ---
    image_pts, _ = cv.projectPoints(vertices, rvec, tvec_corr, K, dist)

    # --- Carregar imagem original ---
    img = cv.imread('src/capturas_realsense/capture_000_color.png')
    if img is None:
        raise FileNotFoundError("Não consegui ler a imagem em 'src/capturas_realsense/capture_000_color.png'")

    # --- Desenhar arestas do paralelepípedo ---
    edges = [
        (0,1),(1,3),(3,2),(2,0),  # face frontal
        (4,5),(5,7),(7,6),(6,4),  # face traseira
        (0,4),(1,5),(2,6),(3,7)   # ligações
    ]
    for i,j in edges:
        p1 = tuple(image_pts[i].ravel().astype(int))
        p2 = tuple(image_pts[j].ravel().astype(int))
        cv.line(img, p1, p2, (0,255,0), 2)

    # --- Desenhar vértices numerados ---
    for idx, p in enumerate(image_pts):
        u,v = p.ravel()
        cv.circle(img, (int(u),int(v)), 4, (0,0,255), -1)
        cv.putText(img, str(idx), (int(u)+5,int(v)-5),
                   cv.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,0), 1)

    # --- Mostrar resultado ---
    cv.namedWindow("Projeção 2D do Objeto", cv.WINDOW_NORMAL)
    cv.imshow("Projeção 2D do Objeto", img)
    cv.waitKey(0)
    cv.destroyAllWindows()

if __name__ == '__main__':
    main()
