import jetson.inference
import jetson.utils
import time

"""
tutorials
    tutorial for setting up source code, libraries, and picture packages
        https://github.com/dusty-nv/jetson-inference/blob/master/docs/building-repo-2.md
    
    source code will be located in 
        /Home/jetson-inference/build/aarch64/bin/my-detection.py
"""

#loading the object detection network
#"ssd-mobilenet-v2" is the library of images to compare live frames to
#threshold is the amount of objects to detect i.e. increase => detect more
net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)
#get center value of detected object
center = net.Detection().Bottom
#locating camera and setting its resolution.
camera = jetson.utils.videoSource("csi://0")      # '/dev/video0' for V4L2
#displaying camera
display = jetson.utils.videoOutput("display://0") # 'my_video.mp4' for file

#create main operating loop to display video
while display.IsStreaming():
    #gets img (or frame) and its corresponding dimensions
    img = camera.Capture()
    #img dimensions
    # imgString = str(img)
    # imgArray = imgString.split()
    #print(f'image info = {imgArray}')
    #detects objects in each frame
    detections = net.Detect(img)
    #shows video
    display.Render(img)
    #shows  the frames per second on the top of display
    display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))
    # time.sleep(3)

# def GetImageDimensions(img):
#     imgString = str(img)
#     imgArray = imgString.split()
#     return imgArray


