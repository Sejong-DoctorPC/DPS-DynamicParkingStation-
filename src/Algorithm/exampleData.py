import pymongo

examples = ['75공3014', '82공3015', '50공2208', '34공2157', '63공1000', '22공7002', '75공9044', '33공9996', '43공2777', '53공1051']

carNumberDB = {str(i + 1):examples[i] for i in range(0, 10)}
carNumberDB['tag'] = "carNumber"
carNumberDB_id = {'tag':"carNumber"}
init_carNumberDB = {str(i + 1):examples[i] for i in range(0, 10)}

newCarNumberDB = {"$set":init_carNumberDB}
def pymongo_script():
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    print(db)
    carNumberDBs = db.carNumberDB
    carNumberDBs.insert_one(carNumberDB)
    #sectors.insert_one(sector)
    
if __name__ == "__main__":
   pymongo_script()
   
