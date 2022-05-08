"""
Object detection module
using: Viola jhones Method

by: Antonino Nguyen
School: Cal Poly Pomona
References: https://www.youtube.com/watch?v=CRpW9wrRKx4
"""

import cv2

"""
haarcascasdes can be found on openCV website
"""
def findObjects(img, objectCascade, scaleF = 1.1, minN = 4):
    """
    finds objects using the haarcascade file
    :param img: Image in which the object needs to be found
    ;param objectCascade: objec cascade created with cascade classifier
    :param scaleF: how much the image size is reduced at each image scale
    :param minN: how many neighbours each rectangle should have to accept as valid
    :return: image with the rectangles drawn and the bounding box ino
    """

    imgObjects = img.copy()
    imgGray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #(imgGray, scale factor, minimum naibors)
    objects = objectCascade.detectMultiScale(imgGray,scaleF, minN)
    for (x,y,w,h) in objects:
        cv2.rectangle(img,(x,y),(x+w, y+h),(255,0,255),2)
    
    return imgObjects, objects



def main():
    img = cv2.imread("Resources/face.jpg")
    img = cv2.resize(img, (0,0), None, 0.5, 0.5)
    objectCascade = cv2.CascadeClassifier("Resources/haarcascades/haarcascade_frontalface_default.xml")
    imgObjects, objects = findObjects(img, objectCascade)
    cv2.imshow("Output",img)
    cv2.waitKey(0)


if __name__ == "__main__":
    main()