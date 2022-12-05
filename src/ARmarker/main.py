# aruco Detection lib
import numpy as np
import pandas as pd
import cv2
from cv2 import aruco
import copy

# protocol lib
#from serial import Serial
import pymongo



# data
markers = [0] * 37
markers_copy = [1] * 37
zone_id = [i for i in range(1, 37)]
#sector_id={"_id":"638bd366ff6bd52512624bf5"}

# mongoDB
def zero2one(n):
    if n == 1:
        return 0
    elif n == 0:
        return 1
def pymongo_script():
    # global variable
    global zone_id

    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE
    client = pymongo.MongoClient(uri)
    db = client.get_database('test')
    #print(db)
    parkings = db.parking
    for i in zone_id:
        parkings.update_one(
            {"zone": i}, 
            {"$set":
                {
                    "state": zero2one(markers[i-1]),
                }
            }
        )

# aruco marker detect function
def findArucoMarkers(img, markerSize=6, totalMarker=250, draw=True):
    # global variable
    global markers
    global markers_copy
    global sector
    global newSector

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = 255 - gray
    cv2.imshow("window_1", gray)
    key = getattr(aruco, f"DICT_{markerSize}X{markerSize}_{totalMarker}")
    arucoDict = aruco.Dictionary_get(key)
    arucoParam = aruco.DetectorParameters_create()
    bboxs, ids, rejected = aruco.detectMarkers(gray, arucoDict, parameters = arucoParam)
    #print(type(ids))
    
    if ids is not None:

        # init data
        markers = [0] * 37
        ids = ids.tolist()

        # save data
        for i in ids:
            markers[i[0] - 1] = 1

        # transport db
        if markers != markers_copy: # someting change in array
            print("different")
            pymongo_script()
            markers_copy = copy.copy(markers)

            # print   
            for i in range(6):
                index = 6 * i
                print(markers[index:index + 6])
        if draw:
            aruco.drawDetectedMarkers(gray, bboxs)
        else : print("same")

def activateCam():
    # turn on Cam
    cam = cv2.VideoCapture(cv2.CAP_DSHOW + 0)
    cam = cv2.VideoCapture(0)
    cam.set(cv2.CAP_PROP_FRAME_WIDTH, 3840)
    cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

    # Exception: 
    if not cam.isOpened():
        print("Could not open webcam")
        exit()
    while cam.isOpened():
        status, img = cam.read()
        findArucoMarkers(img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    # turn off Cam
    cam.release()
    cv2.destroyAllWindows()


# main
if __name__ == "__main__":
    activateCam()

