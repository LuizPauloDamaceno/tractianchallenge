#!/usr/bin/python3

import socket, time

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('192.168.2.149', 333))
while True:
	data = client_socket.recv(512)
	print(data)
	f = open("esp.txt", "a")
	f.write(data.decode("utf-8" ) + "\n")
	f.close()
