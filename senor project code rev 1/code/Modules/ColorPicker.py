# from djitellopy import tello

import cv2

import numpy as np
# import LaneLines
displayWidth = 320
displayHeight = 240
flipCamera = 2

frameWidth = 480

frameHeight = 360
colorPickerVals = []



# me = tello.Tello()

# me.connect()

# print(me.get_battery())

# me.streamon()

def empty(a):

    pass

cv2.namedWindow("HSV")

cv2.resizeWindow("HSV", 640, 240)

cv2.createTrackbar("HUE Min", "HSV", 0, 179, empty)

cv2.createTrackbar("HUE Max", "HSV", 179, 179, empty)

cv2.createTrackbar("SAT Min", "HSV", 0, 255, empty)

cv2.createTrackbar("SAT Max", "HSV", 255, 255, empty)

cv2.createTrackbar("VALUE Min", "HSV", 0, 255, empty)

cv2.createTrackbar("VALUE Max","HSV", 255, 255, empty)

#cap = cv2.VideoCapture(1)

frameCounter = 0
def ColorPicker():
    success = True
    # camera settings
    cameraSettings ='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method=' + str(flipCamera) + ' ! video/x-raw, width=' + str(displayWidth) + ', height='+str(displayHeight)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
    #camera
    camera = cv2.VideoCapture(cameraSettings)
    while success == True:
        colorPickerVals.clear()
        getFrame, frame = camera.read()
        # img = me.get_frame_read().frame
        # img = cv2.VideoCapture('test_video.mp4')
        #_, img = cap.read()
        img = frame
        try:
            img = cv2.resize(img, (frameWidth, frameHeight))
        except:
            break

        img = cv2.flip(img,0)

        imgHsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        h_min = cv2.getTrackbarPos("HUE Min", "HSV")

        h_max = cv2.getTrackbarPos("HUE Max", "HSV")

        s_min = cv2.getTrackbarPos("SAT Min","HSV")

        s_max = cv2.getTrackbarPos("SAT Max", "HSV")

        v_min = cv2.getTrackbarPos("VALUE Min", "HSV")

        v_max = cv2.getTrackbarPos("VALUE Max", "HSV")

        lower = np.array([h_min, s_min, v_min])

        upper = np.array([h_max, s_max, v_max])

        mask = cv2.inRange(imgHsv, lower, upper)

        result = cv2.bitwise_and(img, img, mask=mask)

        # print(f'[{h_min},{s_min},{v_min},{h_max},{s_max},{v_max}]')

        mask = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
        # mask = cv2.invert(mask) 
        hStack = np.hstack([img, mask, result])

        cv2.imshow('Horizontal Stacking', hStack)
        colorPickerVals.append([h_min, s_min, v_min, h_max, s_max, v_max])
        if cv2.waitKey(1) == ord('q'):
            colorPickerVals.append([h_min, s_min, v_min, h_max, s_max, v_max])
            success = False

    print(f'colorPickerVals = {colorPickerVals}')
    #always commented
    # cap.release()

    cv2.destroyAllWindows()
if __name__ == '__main__':
    ColorPicker()
    print(f'colorPickerVals = {colorPickerVals}')
