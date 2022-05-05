import serial
import os, sys

if len(sys.argv) != 3:
    print("certupload.py <port> <certdir>")
    exit()

files = ["AmazonRootCA1.pem",
         "AmazonRootCA3.pem",
         "certificate.pem.crt",
         "private.pem.key",
         "public.pem.key"];

ser = serial.Serial(
    port=sys.argv[1],
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

for fname in files:
    f = open(sys.argv[2] + fname)
    
    ser.write(bytes("AT+QFDEL=\"" + fname + "\"\r", encoding='utf8'))
    while 1:
        line = ser.read_until(b"\r\n")
        print(line)
        if line == b"OK\r\n" or line == b"+CME ERROR: 405\r\n":
            break;
    
    f.seek(0, os.SEEK_END)
    ser.write(bytes("AT+QFUPL=\"" + fname + "\"," + str(f.tell()) + "\r", encoding='utf8'))
    while 1:
        line = ser.read_until(b"\r\n")
        print(line)
        if line == b"CONNECT\r\n":
            break;
    f.seek(0, os.SEEK_SET)
    
    ser.write(bytes(f.read(), encoding='utf8'))
    ser.write(b"\x1A")
    ser.read_until(b"OK\r\n")
    f.close();

ser.close()