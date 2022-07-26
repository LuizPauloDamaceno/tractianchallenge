#!/usr/bin/python3
import time, serial

baudrate=115200
serialport='/dev/ttyACM0'

datapath='../tools/randomfile.txt'

f = open(datapath, "r")

ard = serial.Serial(serialport, baudrate)

ard.close()

for line in f:
	ard.open()
	ard.write(str.encode(line+'\r\n'))
	ard.close()
	time.sleep(0.175)
