import argparse
import socketio
from pythonosc import osc_message_builder
from pythonosc import udp_client
from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
import asyncio
import time

#ipとポートのセッティング
OF_IP = "127.0.0.1"
OF_PORT = 5006

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8005

#各種変数
path = [10, 0] #パス
accData = [0.0, 0.0, 0.0] #加速度データ
counter = 0 #テスト用変数

#フレームレート計測用
initTime = 0.0
frameCounter = 0

#データを送信するコールバック関数
def send_message(outputStatus):

    #print("sending status...")
    client.send_message("/status", outputStatus)
    
    return 0

def send_message_acc(accX, accY, accZ):

    #print("sending acc...")
    client.send_message("/acc/x", accX)
    client.send_message("/acc/y", accY)
    client.send_message("/acc/z", accZ)
    
    return 0

#データを受信したときのコールバック関数
def filter_handler(address, *args):
    global path
    print("recieved!!")
    if(address == "/path/x"):
        path[0] = args[0]
    
    if(address == "/path/y"):
        path[1] = args[0]
    


#クライアントのセットアップ
parser = argparse.ArgumentParser()
parser.add_argument("--ip", default=OF_IP,
                        help="The ip of the OSC server")
parser.add_argument("--port", type=int, default=OF_PORT,
                        help="The port the OSC server is listening on")
args = parser.parse_args()

client = udp_client.SimpleUDPClient(args.ip, args.port)

#サーバーのセットアップ
dispatcher = Dispatcher()
dispatcher.map("/path/x", filter_handler)
dispatcher.map("/path/y", filter_handler)

#ソケット通信のセットアップ
sio = socketio.Client()

@sio.event
def connect():
    print("I'm connected!")

@sio.on('mouse')
def on_message(data):
    #print('Receive Data ', data)

    global accData
    accData[0] = data["x"]
    accData[1] = data["y"]
    accData[2] = data["z"]


#メインループ
async def loop():
    
    try:
        while True:
            global path, accData
            
            '''
            if posX == 9000 and posY == 9000 :
                send_message(1) #oFに到達したことを送信
            else:
                send_message(0) #oFに到達していないことを送信
            '''
            
            send_message_acc(accData[0], accData[1], accData[2])

            #以下フレームレート・通信確認用
            global initTime, frameCounter, counter
            t = time.time() - initTime
            frameCounter += 1
            if(t > 1.0):
                print("fps:", frameCounter)
                print("path:", path)
                print("acc", accData)
                frameCounter = 0
                counter += 1
                initTime = time.time()

                if(counter % 3 == 0):
                    send_message(1)
                else:
                    send_message(0)

            await asyncio.sleep(0.01)
    except KeyboardInterrupt:
        print('!!FINISH!!')


#同期の初期セットアップ
async def init_main():
    server = AsyncIOOSCUDPServer((SERVER_IP, SERVER_PORT), dispatcher, asyncio.get_event_loop())
    transport, protocol = await server.create_serve_endpoint()  # Create datagram endpoint and start serving
    
    global initTime
    initTime = time.time()
    await loop()  # Enter main loop of program

    transport.close()  # Clean up serve endpoint


sio.connect('https://od2021-jp-kokoro.herokuapp.com/')

asyncio.run(init_main())
