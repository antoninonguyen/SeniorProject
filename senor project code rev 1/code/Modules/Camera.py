import cv2 as cv
displayWidth = 320
displayHeight = 240
flipCamera = 2
# print(cv.__version__)

# camera settings
cameraSettings ='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method=' + str(flipCamera) + ' ! video/x-raw, width=' + str(displayWidth) + ', height='+str(displayHeight)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
#camera
camera = cv.VideoCapture(cameraSettings)
# print(cv.getBuildInformation())

#loops throug each frame of the camera to display video
while True:
    #getFrame returns a bool value 1 for successfully getting frame.
    #Frame is the actual image of the frame
    getFrame, frame = camera.read()
    frame = cv.rotate(frame, cv.ROTATE_180)
    cv.imshow('piCamera', frame)
    #set up key to exit camera
    #q will exit loop and stQop showing video
    if cv.waitKey(1) == ord('q'):
        break
camera.release()
cv.destroyAllWindows()
