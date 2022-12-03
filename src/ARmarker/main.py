# aruco Detection lib
import numpy as np
import pandas as pd
import cv2
from cv2 import aruco

# protocol lib
#from serial import Serial
import pymongo



# data
markers = [0] * 36
sector = {"{}".format(key):1 for key in range(1, 37)}
sector["tag"] = "aruco"
sector_id={"tag":"aruco"}
#sector_id={"_id":"638bd366ff6bd52512624bf5"}
newSector = {"$set":{format(key):1 for key in range(1, 37)}}

# mongoDB
def pymongo_script():
    #uri = "mongodb+srv://yblee1223:smarcle2017@cluster0.qb7zx87.mongodb.net/test" # MY indivisial db
    #uri = "mongodb://localhost:27017/" # local
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE
    client = pymongo.MongoClient(uri)
    db = client.get_database('test')
    #print(db)
    sectors = db.sectors
    print(newSector)
    sectors.update_one(sector_id, newSector)

# aruco marker detect function
def findArucoMarkers(img, markerSize=6, totalMarker=250, draw=True):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = 255 - gray
    # cv2.imshow("window_2", gray)
    key = getattr(aruco, f"DICT_{markerSize}X{markerSize}_{totalMarker}")
    arucoDict = aruco.Dictionary_get(key)
    arucoParam = aruco.DetectorParameters_create()
    bboxs, ids, rejected = aruco.detectMarkers(gray, arucoDict, parameters = arucoParam)
    print(type(ids))
    
    if ids is not None:
        # init data
        markers = [0] * 36
        init_sector = {"{}".format(key):1 for key in range(1, 37)}
        ids = ids.tolist()

        # save data
        for i in ids:
            markers[i[0] - 1] = 1
            init_sector[str(i[0])] = 0
        newSector["$set"] = init_sector
        # transport db
        pymongo_script()

        # print   
        for i in range(6):
            index = 6 * i
            print(markers[index:index + 6])
    if draw:
        aruco.drawDetectedMarkers(gray, bboxs)

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
