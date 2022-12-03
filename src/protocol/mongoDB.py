import pymongo

sector = {"{}".format(key):1 for key in range(1, 37)}
#sector_id={"_id":"638bd366ff6bd52512624bf5"}
sector["tag"] = "aruco"
sector_id={"tag":"aruco"}
newSector = {"$set":{format(key):7 for key in range(1, 37)}}

def pymongo_script():
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    print(db)
    sectors = db.sectors
    #sectors.update_one(sector, newSector)
    sectors.insert_one(sector)
    
if __name__ == "__main__":
   pymongo_script()
   
