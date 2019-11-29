import serial
import socket               # Import socket module

treshold = 12

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
# socket programming
s = socket.socket()
host = socket.gethostname()
port = 12345

while True:
    line = ser.readline()
    try:
        if(int(line[10:]) < treshold):
            s.connect((host, port))
            s.send("trash full")
            break

    except:
        pass




