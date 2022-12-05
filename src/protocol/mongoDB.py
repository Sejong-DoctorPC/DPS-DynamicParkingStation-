import pymongo
zone_id = [i for i in range(1, 37)]
templete = {
  "zone": 1,
  "type": 0,
  "state": 0,
  "parker": None,
  "__v": 0
}

def pymongo_script():
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    print(db)
    sample = db.parkings
    for i in zone_id:
        # sample.insert_one(
        #     {
        #     "zone": i,
        #     "type": 0,
        #     "state": 0,
        #     "light": 0,
        #     "parker": None,
        #     "__v": 0
        #     }
        # )
        sample.update_one(
            {"zone": i}, 
            {"$set":
                {
                "zone": i,
                "type": 0,
                "state": 0,
                "light": 0,
                "parker": None,
                "__v": 0
                }
            }
        )
    #sectors.insert_one(sector)
    
if __name__ == "__main__":
   pymongo_script()
   
