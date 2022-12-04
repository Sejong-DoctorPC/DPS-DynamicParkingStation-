import pymongo
zone_id = [i for i in range(1, 37)]
sector = {"{}".format(key):{"place":1, "carNumber": 0, "disabled": 0} for key in range(1, 37)}
init_sector = {"{}".format(key): {"place":1, "carNumber": 0, "disabled": 0} for key in range(1, 37)}

newSector = {"$set":init_sector}
def pymongo_script():
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    print(db)
    sectors = db.sectors
    for zone in zone_id:
        sectors.update_one({"zone":zone}, newSector)
    #sectors.insert_one(sector)
    
if __name__ == "__main__":
   pymongo_script()
   
