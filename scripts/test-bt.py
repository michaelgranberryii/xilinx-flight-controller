# Import packages
import os
import serial
import time

# Initialize HC-05 Bluetooth module and bind r
# os.system('sudo rfcomm bind rfcomm0 98:D3:02:96:6E:D4')
BTserialChannel = serial.Serial("/dev/rfcomm0", baudrate=38400)


data = "abc\n\r".encode()

try:
    BTserialChannel.write(data) 
    print(data)
except:
    # Close
    os.system("echo 'ERORR: COULDNT SEND'")
    exit()