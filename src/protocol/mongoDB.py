import pymongo

sector = {"{}".format(key):{"place":1, "carNumber": 0, "disabled": 0} for key in range(1, 37)}
#sector_id={"_id":"638bd366ff6bd52512624bf5"}
sector["tag"] = "aruco"
sector_id={"tag":"aruco"}
init_sector = {"{}".format(key): {"place":1, "carNumber": 0, "disabled": 0} for key in range(1, 37)}
init_sector[str(7)]["place"] = 0
print(init_sector['7']["place"])
newSector = {"$set":init_sector}
def pymongo_script():
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    print(db)
    sectors = db.sectors
    sectors.update_one(sector, newSector)
    #sectors.insert_one(sector)
    
if __name__ == "__main__":
   pymongo_script()
   
