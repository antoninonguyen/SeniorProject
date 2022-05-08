import serial
import time
import SerialModule2


if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyACM0", 9600, timeout=5)
    while 1:
        # getFrame, frame = camera.read()
        # imgRotate = cv2.rotate(frame, cv2.ROTATE_180)
        SerialModule2.sendData(ser,"l")
        SerialModule2.sendData(ser,"r")
