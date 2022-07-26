# tractianchallenge
Tractian's Challenge for Hardware R&D - Final resources and resolution

Initially, i've decided to make the communication bridge (Tx and Rx systems) most modular as possible. So, in this project we have four parts:

	1 - The data what's going to be sent;
	2 - The board who talks (or not) with some serial wireless transceiver;
	3 - The board or client with also some wireless transceiver;
	4 - The incoming data reconstruction program (embedded at the board in step 3 or not).

We have the follwing situations:

| Transmitting device | Fragmentation method | Receiving device | Reconstruction method | 
|------|------|------|------|
| Arduino Mega | Python readlines of original file + SerialBuffer getting SoftwareSerial data | Arduino Mega | Python appending incoming serial lines to a file |
