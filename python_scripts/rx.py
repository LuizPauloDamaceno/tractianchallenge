#!/usr/bin/python3
import time
import serial
import sys

baud=57600

arduino = serial.Serial('/dev/ttyUSB1', baud, timeout=10)
while True:
	f = open("rx.txt", "a")
	a = arduino.readline().decode('ISO-8859-1').strip('\n').strip('\r')
	f.write(a + '\n')
	f.close()
