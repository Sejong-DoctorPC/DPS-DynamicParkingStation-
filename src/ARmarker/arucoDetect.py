
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mlt
import cv2
from cv2 import aruco
from flask import Flask

# aruco marker detect function
def findArucoMarkers(img, markerSize=6, totalMarker=250, draw=True):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = 255 - gray
    # cv2.imshow("window_2", gray)
    key = getattr(aruco, f"DICT_{markerSize}X{markerSize}_{totalMarker}")
    arucoDict = aruco.Dictionary_get(key)
    arucoParam = aruco.DetectorParameters_create()
    bboxs, ids, rejected = aruco.detectMarkers(gray, arucoDict, parameters = arucoParam)
    #print(type(ids))
    markers = [0] * 36
    markers[2] = 1
    if ids is not None:
        ids = ids.tolist()
        for i in ids:
            markers[i[0] - 1] = 1
    # for i in range(6):
    #     index = 6 * i
    #     print(markers[index:index + 6])
    # if draw:
    #     aruco.drawDetectedMarkers(gray, bboxs)

        
def activateCam():
    status, img = cam.read()
    findArucoMarkers(img)
    if status:
        #cv2.imshow("window_1", 255 - img)
        pass
    # turn off Cam
    cam.release()
    cv2.destroyAllWindows()



# turn on Cam
cam = cv2.VideoCapture(0)
cam.set(cv2.CAP_PROP_FRAME_WIDTH, 3840)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

# Exception: 
if not cam.isOpened():
    print("Could not open webcam")
    exit()

# Flask
markers = [0] * 36
cnt = 0
app = Flask(__name__)
@app.route('/')
def home():
    status, img = cam.read()
    findArucoMarkers(img)
    return markers

    
if __name__ == "__main__":
    app.run(debug=True)








