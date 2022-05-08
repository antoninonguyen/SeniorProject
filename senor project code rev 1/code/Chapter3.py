import cv2
import numpy as np

img = cv2.imread("Resources/humans_8.jpg")
#size of image
#(height, width, color (3 = Blue Green Red,))
print(img.shape)

#resize
#by pixels
imgResize1 = cv2.resize(img, (640,480))

#by scale
#none is output, last values is scale of width and height
imgResize2 = cv2.resize(img, (0,0), None, 0.5, 0.5)
print(imgResize2.shape)

#crop an image
#[y,x]
imgCrop = img[50:155,210:285]

cv2.imshow("Image", img)
cv2.imshow("Image",imgResize1)
cv2.imshow("Image",imgResize2)
cv2.imshow("Image",imgCrop)
cv2.waitKey(0)



