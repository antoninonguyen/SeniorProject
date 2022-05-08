import numpy as np
import matplotlib.pylab as plt

import cv2
#region Second camera
"""
second camera
"""
# cap = cv2.VideoCapture(1)
"""
end of second camera
"""
#endregion
hsvVals = [92,19,190,147,53,255]
print(f'colorPickerVals = {hsvVals}')

sensors = 3

threshold = 0.2

width, height = 480, 360

startPoint = (width - width,int(height/2))

endPoint = (int(width),int(height/2))

centerLineColor = (0,255,0)

senstivity = 3  
thicknessCenterLine = 2

weights = [-25, -15, 0, 15, 25]

red = (0, 0, 255)

fSpeed = 15

curve = 0

def thresholding(img):
    
    bw = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #region Reverse Code
    """
    possible reverse img code
    """
    # print(f'bw = {bw}')
    # bw = np.where(bw >= 200, 0, 255) 
    # print(f'bw before {bw}')
    # secondbw = np.where(bw == 255, 255, 0) 
    # thirdvw =  np.where(bw == 255, 255, 0)
    # bw = cv2.merge([bw,secondbw,thirdvw])
    # print(f'bw after {bw}')
    # P = cv2.cvtColor(bw, cv2.COLOR_GRAY2BGR)
    # print(iw,jw) 
    # print(bw[i])
    # print(len(bw[1]))
    # print(bw)
    # print(type(bw))
    # iw, jw = np.where(mask == 255)
    # ib, jb = np.where(mask == 0)
    # x=np.empty(mask.shape[:2])
    # x = np.where(mask == 255,0,255)
    """
    possible reverse img code end
    """
    #endregion
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    lower = np.array([hsvVals[0], hsvVals[1], hsvVals[2]])

    upper = np.array([hsvVals[3], hsvVals[4], hsvVals[5]])

    mask = cv2.inRange(hsv, lower, upper)
    
    return mask

def drawCenterImg(img):
    image = cv2.line(img, startPoint, endPoint, centerLineColor, thicknessCenterLine)
    image = cv2.line(img,(240,180-10), (240,180+10), centerLineColor, 2)
    image = cv2.line(img,(240-10,180), (240+10,180), centerLineColor, 2)
    image = cv2.circle(img, (240, 180), 10, centerLineColor, 2)
    return image

def drawCenterContour(img,cx,cy):
    image = cv2.line(img,(cx,cy-10), (cx,cy+10), (0, 0, 255), 2)
    image = cv2.line(img,(cx-10,cy), (cx+10,cy), (0, 0, 255), 2)
    image = cv2.line(img,(cx,180-10), (cx,180+10), (0, 0, 255), 2)
    image = cv2.line(img,(cx,180), (240,180), (255, 0, 0), 2)
    image = cv2.circle(img, (cx, cy), 10, (0, 0, 255), 2)
    if cx < 240:
        img = cv2.putText(image, f'delta x = {240-cx} pixels', (10,20), cv2.FONT_HERSHEY_SIMPLEX, .5, (255, 0, 255), 1, cv2.LINE_AA)
    else:
        img = cv2.putText(image, f'delat x = {cx-240} pixels', (10,20), cv2.FONT_HERSHEY_SIMPLEX, .5, (255, 0, 255), 1, cv2.LINE_AA)
    return image

def getContours(imgThres, img):
    
    cx = 0

    contours, hieracrhy = cv2.findContours(imgThres, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    if len(contours) != 0:

        biggest = max(contours, key=cv2.contourArea)

        x, y, w, h = cv2.boundingRect(biggest)

        cx = x + w // 2

        cy = y + h // 2
        
        cv2.drawContours(img, biggest, -1, (255, 0, 255), 7)

        drawCenterImg(img)

        drawCenterContour(img,cx,cy)
        
    return cx

def getSensorOutput(imgThres, sensors):

    imgs = np.hsplit(imgThres, sensors)

    totalPixels = (img.shape[1] // sensors) * img.shape[0]

    senOut = []

    for x, im in enumerate(imgs):

        pixelCount = cv2.countNonZero(im)

        if pixelCount > threshold * totalPixels:

            senOut.append(1)

        else:

            senOut.append(0)

    return senOut

def sendCommands(senOut, cx):
    """
    alternative steering function
    """
    global curve

    lr = (cx - width // 2) // senstivity

    lr = int(np.clip(lr, -10, 10))

    if 2 > lr > -2: lr = 0

    ## turning

    if   senOut == [1, 0, 0]: curve = weights[0]

    elif senOut == [1, 1, 0]: curve = weights[1]

    elif senOut == [0, 1, 0]: curve = weights[2]

    elif senOut == [0, 1, 1]: curve = weights[3]

    elif senOut == [0, 0, 1]: curve = weights[4]

    elif senOut == [0, 0, 0]: curve = weights[2]

    elif senOut == [1, 1, 1]: curve = weights[2]

    elif senOut == [1, 0, 1]: curve = weights[2]

    
def getCenterValue(cx):
    """
    gets center of line detected
    """
    turndistance = 0
    leftMost = 0
    rightMost = 480
    center = cx 
    if cx < 480:
        turndistance = 480 - cx
    elif cx > 480:
        turndistance = cx - 480
    else:
        turndistance = 0
    return turndistance


if __name__ == "__main__":
    img = cv2.imread("Resources/face.jpg")

    img = cv2.resize(img, (width, height))

    imgThres = thresholding(img)
    
    sendCommands(senOut, cx)

    cv2.imshow("Output", img)

    cv2.imshow("Path", imgThres)

    cv2.waitKey(0)

    