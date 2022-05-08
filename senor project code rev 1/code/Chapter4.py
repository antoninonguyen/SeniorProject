import cv2 
import numpy as np 

"""
DEF:
images are just matricies with values
numpy will help create this image
np.zeros will create an empty image
np.uinit8 will convert this image into 
an 8 bit array 8 bit = 2^8 = 255
img[:] = B, G, R (Blue,Green,Red)
"""
img = np.zeros((512,512,3), np.uint8)

#changing color of blank image
#255,255,255 is a white image
img[:] = 255, 255, 255

#drawing a circle
#parameters
#(img,(x center point, y center point),radius,color, thickness)
cv2.circle(img, (256,256),150, (0,69,255),cv2.FILLED)
#rectangle
#parameters
#(img, left point, bottom right value, color, thickness)
cv2.rectangle(img, (130,226),(382,286),(255,255,255),cv2.FILLED)
#lines
#parameters
#(img,starting point, ending point)
cv2.line(img, (130,296),(382,296),(255,255,255),2)
#text
#parameters
#(img, string, starting point, font, scale, color, thickness)
cv2.putText(img, "Autonomous Cart", (137,262),cv2.FONT_HERSHEY_DUPLEX, 0.75, (0,69,255), 2)
cv2.imshow("Image", img)
cv2.waitKey(0)