import numpy as np 
import cv2
import LaneLines
import SerialModule
import serial
# import ColorPicker

def SendData(data, digits):
    
    myString = "$"
    for d in data:
        myString += str(d).zfill(digits)
    print(f'mystring = {myString}')
    return myString
#camera constances
displayWidth = 480
displayHeight = 360
flipCamera = 2
# camera settings
cameraSettings ='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method=' + str(flipCamera) + ' ! video/x-raw, width=' + str(displayWidth) + ', height='+str(displayHeight)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
#camera
camera = cv2.VideoCapture(cameraSettings)
# print(cv.getBuildInformation())
#activation
activateSteering = 000
ser = serial.Serial("/dev/ttyACM0", 9600, timeout=5)
# ser = serial.Serial(SerialModule.SERIALPORT, SerialModule.BAUDRATE, timeout = SerialModule.TIME)
# activateColorPicker = input("do you want to tune line tracking image values? y/n")
# if activateColorPicker == "y":
#     if activateColorPicker == "y":
#         ColorPicker()
#         hsvVals = ColorPicker.colorPickerVals
#         print(f'hsvVals = {hsvVals}')
#     elif activateColorPicker == "n" :
#         break
#     else:
#         print("invalid entry please make sure characters are lowercase")
while 1:
    #get image
    #getFrame returns a bool value 1 for successfully getting frame.
    #Frame is the actual image of the frame
    getFrame, frame = camera.read()
    imgRotate = cv2.rotate(frame, cv2.ROTATE_180)
    # cv2.imshow('piCamera', frame)
    #set up key to exit camera
    #q will exit loop and stop showing video
    # if cv2.waitKey(1) == ord('q'):
    #     break
    
    #send img for processing
    img = cv2.resize(imgRotate, (LaneLines.width, LaneLines.height))

    # img = cv2.flip(img, 0)

    imgThres = LaneLines.thresholding(img)
    #lane center value
    cx = LaneLines.getContours(imgThres, img)  ## For Translation
    # center = LaneLines.getCenterValue(cx)
    """
    serial communication part
    """
    print(f'cx = {cx}')
    FrontMotor = SendData([cx,0,0],3)
    ser.write(b'FrontMotor\n')
    
    # inputStr = ser.readline().decode("utf-8",errors='replace').strip()
    # print("Read input back: " + inputStr)

    #send steering data
    # ret2 = SerialModule.FrontMotorData(ser,FrontMotor,3)
    print("front motor data")
    # print(ret2, FrontMotorInputStr)
    # print(f'center value = {center}')
    # print(f'cx = {cx}')
    # print(f'successfully submitted {ret2}')
    cv2.imshow("Output", img)

    cv2.imshow("Path", imgThres)

    cv2.waitKey(1)
    if cv2.waitKey(1) == ord('q'):
        break
camera.release()
cv.destroyAllWindows()