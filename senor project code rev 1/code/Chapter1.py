import cv2 
#print(cv2.__version__)

# ### importing an image
# img = cv2.imread("Resources/humans_8.jpg")
# cv2.imshow("Output",img)
# cv2.waitKey(0)

# ### import video

# frameWidth = 640
# frameHeight = 480
# cap = cv2.VideoCapture("Resources/test_video.mp4")
# while True:
#     success, img = cap.read()
#     img = cv2.resize(img,(frameWidth, frameHeight))
#     cv2.imshow("Results", img)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

### run webcam

frameWidth = 640
frameHeight = 480
flipCamera = 2
cameraSettings ='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method=' + str(flipCamera) + ' ! video/x-raw, width=' + str(frameWidth) + ', height='+str(frameHeight)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
cap = cv2.VideoCapture(cameraSettings)

while True:how 
while True:how 
while True:how 
    success, img = cap.read()
    img = cv2.resize(img,(frameWidth, frameHeight))
    cv2.imshow("Results", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    
