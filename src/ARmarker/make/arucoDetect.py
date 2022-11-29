
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mlt
import cv2
from cv2 import aruco

# aruco marker detect function
def findArucoMarkers(img, markerSize=6, totalMarker=250, draw=True):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cv2.imshow("window_2", gray)
    key = getattr(aruco, f"DICT_{markerSize}X{markerSize}_{totalMarker}")
    arucoDict = aruco.Dictionary_get(key)
    arucoParam = aruco.DetectorParameters_create()
    bboxs, ids, rejected = aruco.detectMarkers(gray, arucoDict, parameters = arucoParam)
    print(type(ids))
    markers = [0] * 36
    if ids is not None:
        ids = ids.tolist()
        for i in ids:
            markers[i[0] - 1] = 1
        
    for i in range(6):
        index = 6 * i
        print(markers[index:index + 6])
    if draw:
        aruco.drawDetectedMarkers(img, bboxs)

        
def activateCam():
    # turn on Cam
    cam = cv2.VideoCapture(0)

    # Exception: 
    if not cam.isOpened():
        print("Could not open webcam")
        exit()

    while cam.isOpened():
        status, img = cam.read()
        findArucoMarkers(img)
        if status & toggle:
            cv2.imshow("window_1", img)
            pass

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    # turn off Cam
    cam.release()
    cv2.destroyAllWindows()

# main
markers = [0] * 36
toggle = 0
if __name__ == "__main__":
    toggle = 1
activateCam()








