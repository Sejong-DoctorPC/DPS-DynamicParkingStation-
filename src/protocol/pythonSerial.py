import serial
import time
import pymongo

py_serial = serial.Serial(
    # Mac : 포트는 검색해서 linux로 변환
    port = '/dev/cu.usbmodem101',
    
    # 보드 레이트 (통신 속도)
    baudrate=9600,
)

def protocol_D2P(): # mongo db to python
    uri = "mongodb+srv://yonghyun:47529722@diyparking.ddqzn68.mongodb.net/?retryWrites=true&w=majority" # USPACE

    client = pymongo.MongoClient(uri)
    db = client.get_database('test')  
    #print(db)
    DPS = db.DPS
    dps = DPS.find_one()
    print(dps)
    return dps

def decide_cmd(dps):
    print(dps)
    return "M{0}, E{1}, S{2}".format(dps["mode"], dps["exit"], dps["light_sector"])

def protocol_P2A(dps): # python to arduino
    
    while True:
        cmd = decide_cmd(dps)
        print(cmd)
        py_serial.write(cmd.encode())
        # time.sleep(0.1)
        time.sleep(10)
        if py_serial.readable():    
            # 들어온 값이 있으면 값을 한 줄 읽음 (BYTE 단위로 받은 상태)
            # BYTE 단위로 받은 response 모습 : b'\xec\x97\x86\xec\x9d\x8c\r\n'
            response = py_serial.readline()
            print(response)
            # 디코딩 후, 출력 (가장 끝의 \n을 없애주기위해 슬라이싱 사용)
            print(response[:len(response)-1].decode())
if __name__ == "__main__":
    global dps
    dps = protocol_D2P()
    #protocol_P2A(dps)