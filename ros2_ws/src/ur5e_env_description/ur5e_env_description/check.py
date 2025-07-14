import cv2 as cv

img = cv.imread('src/capturas_realsense/capture_000_color.png')
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

# tente primeiro o SB
ret, corners = cv.findChessboardCornersSB(
    gray,
    (5, 21),
    flags=cv.CALIB_CB_EXHAUSTIVE + cv.CALIB_CB_ACCURACY
)
if ret:
    print("✅ SB detectou 5×21!")
    cv.drawChessboardCorners(img, (5, 21), corners, ret)
    cv.imwrite('src/capturas/captura1.png', img)
else:
    print("SB falhou, vamos para a próxima estratégia…")

cv.imshow('Padrão SB', img)
cv.waitKey(0)
cv.destroyAllWindows()
