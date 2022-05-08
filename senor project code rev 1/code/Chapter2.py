import cv2
import numpy as np

"""
5 main function in openCV that alter 
"""

### importing an image
img = cv2.imread("Resources/humans_8.jpg")
imgGray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
imgBlur = cv2.GaussianBlur(imgGray,(7,7),0)
#Canny only outputs black background and white edges
# the values are imgage, and thresh hold values
imgCanny = cv2.Canny(imgBlur, 100, 150)
# dilate increases the thickness of the edges that we canny'd
# kernel turns the picture into a bit array
#increase thickness of the lines by increasing iterations
kernel = np.ones((5,5), np.uint8)
imgDia = cv2.dilate(imgCanny,kernel,iterations=1)
#erode function decreases the thickness of the edges
imgErode = cv2.erode(imgDia,kernel,iterations=1)

cv2.imshow("Output",img)
cv2.imshow("Output",imgGray)
cv2.imshow("Output",imgBlur)
cv2.imshow("Output",imgCanny)
cv2.imshow("Output",imgDia)


cv2.waitKey(0)