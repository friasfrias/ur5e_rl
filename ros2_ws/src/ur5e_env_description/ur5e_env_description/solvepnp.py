import numpy as np
import cv2 as cv
import os

# Critério de terminação para sub-pixel refinement
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

nx, ny = 5, 21
square_size = 0.007

# Geração dos pontos 3D do tabuleiro
objp = np.zeros((nx * ny, 3), np.float32)
objp[:, :2] = np.mgrid[0:nx, 0:ny].T.reshape(-1, 2) * square_size
objp[:, 0] -= (nx - 1) * square_size / 2
objp[:, 1] -= (ny - 1) * square_size / 2

# Carregar imagem
img = cv.imread('src/capturas_realsense/capture_011_color.png')
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
# cv.imshow('Imagem', img)

# Detetar cantos do xadrez
ret, corners = cv.findChessboardCornersSB(gray, (nx, ny), None)

if ret and corners is not None and len(corners) == nx * ny:
    corners2 = cv.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)

    # Carregar matriz K e distorção
    calib = np.load('src/ur5e_env_description/config/calib.npz')
    K = calib['K']
    dist = calib['dist']

    success, rvec, tvec = cv.solvePnP(objp, corners2, K, dist)

    if success:
        print("✅ SolvePnP executado com sucesso.")
        print("rvec:\n", rvec)
        print("tvec:\n", tvec)

        # Converter rotação para matriz 3x3
        R,_ = cv.Rodrigues(rvec)

        # Criar matriz de transformação homogénea 4x4
        T = np.eye(4)
        T[:3, :3] = R
        T[:3, 3] = tvec.squeeze()
        print("🧱 Matriz homogénea da câmara em relação ao padrão:\n", T)

        # Projetar os pontos 3D na imagem
        proj_image_points, _ = cv.projectPoints(objp, rvec, tvec, K, dist)

        # Calcular erro médio de reprojeção
        error = cv.norm(corners2, proj_image_points, cv.NORM_L2) / len(proj_image_points)
        print(f"📏 Erro médio de reprojeção: {error:.3f} px")

        # Desenhar projeções (verde) e corners reais (vermelho)
        for p in proj_image_points:
            x, y = p.ravel()
            cv.circle(img, (int(x), int(y)), 3, (0, 255, 0), -1)
        for p in corners2:
            x, y = p.ravel()
            cv.circle(img, (int(x), int(y)), 3, (0, 0, 255), -1)

        cv.imshow('Comparação pontos projetados vs reais', img)
        cv.waitKey(1000)

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

        print(f'(alpha) = {alpha}')
        print(f'(beta) = {beta}')

        cv.destroyAllWindows()

        # Guardar resultados
        np.savez('camera_to_object.npz', rvec=rvec, tvec=tvec, T=T)
        np.savez('angles.npz', alpha=alpha, beta=beta)

    else:
        print("❌ Erro ao aplicar solvePnP.")
else:
    print("❌ Não foi possível detetar o padrão do xadrez.")
