# Tractian Challenge for R&D

Tractian's Challenge for Hardware R&D - Final resources and resolution

Project directory:
| Folder | Content | 
|------|------|
| arduino_programs | Contains main programs that i've used to test in my arduino boards. |
| eagle_schematics_and_pcb | Base project that can be used for Tx / Rx hardware |
| python_scripts | Base scripts used to send, fragment, reconstruct and append data |
| real_implementations_data | Source data that was transfered through bridges or Wireless and its results at its real uses (phase analysis in time domain) |

Observations: 
	- The data file contains about 36000 points of 13 byte string (coming from a time interval counter that puts data into this file every second with picossecond (pS) resolution).
	- The benchmarks for base tests showed the following results:
		- Bridge mode (case 1): about 15 min to transfer entire data;
		- Wireless mode (case 2): about 2 hours to transfer entire data.

Initially, i've decided to make the communication bridge (Tx and Rx systems) most modular as possible. So, in this project we have four parts:

	1 - The data what's going to be sent;
	2 - The board who talks (or not) with some serial wireless transceiver;
	3 - The board or client with also some wireless transceiver;
	4 - The incoming data reconstruction program (embedded at the board in step 3 or not).

We have the follwing implementations for proof of concept:

| Case | Transmitting device | Fragmentation method | Receiving device | Reconstruction method | 
|------|------|------|------|------|
| 1, wired | Arduino Mega | Python readlines of original file + SerialBuffer getting SoftwareSerial data | Arduino Mega | Python appending incoming serial lines to a file |
| 2, wireless | Arduino Uno | Python readlines of original file + SerialBuffer getting SoftwareSerial data | ESP8266 configured as client in home wireless networking, serving a TCP stream at its port 333 | Python appending incoming socket client data lines to a file |

For case 2, 80m air gap was reached (with few obstachles in the middlepath) by following  diagram:

| Arduino Uno + ESP8266 | ------ air gap (80m) -----> | Wi-Fi router (OpenWrt, TxPower @23dBm) | -----------> | personal computer connected by USB dongle (also 80m from the router) accessing ESP8266 TCP server in LAN |

For the schematics, I've decided to keep uControllers pins unused open. This makes path for futher implementations, depending of the modem model that we want to use. 

Also, make note that i've choosen Atmega328 uController, that can be replaced for few uControllers of different Atmel's family. Of course, few layout settings should be replanned if other uControllers want to be implemmented. 

Concerning the voltage regulating parts, i've choose a regulator that can step up voltage from an ordinary 18650 Li-Ion battery with some quality. We have many decoupling capacitors here because of current peaks that regulator may have an slow response and this may result in loss of packet transfer or even hardware bug. 

If is the case of integrating ESP8266 board (or any other radio, such as LoRa ones) into main uController's board, few R.F. cares should be taken into account, such as:

	1 - Never put an transmitter (of whatever frequency) near to main uControlers XTAL, or injection locking may occur, degrading overall system performance or stopping system working;
	2 - Striplines for antennas are the best design form: it's compact and we can dimension it in accordance with frequency wavelenght, for this, higher Transmitting and Receiving frequency may be optimal, since lower freququencies will have big transmission lines;
	3 - Decoupling inductors and capacitors for power amplifiers are good idea for removing transmission noise from the overall system;
	4 - Avoid 90º lines at PCB, this may irradiate signals and degrade system's performance;

The main schematic and board relies in an external radio device operating by a serial port that is virtual. Any radio device that operates by sending serial data through air will work with this project. Other implementations such as i2c or SPI radios may work with few changings in the project.

The project as it is has the same board for RX and TX, relying on the first concept of "Case 1". Now, some pin descriptions:
| Pin | Description |
|------|------|
| +VBAT / -VBAT | 18650 Battery connections pins |
| MVCC / MGND | Main VCC / GND connections - If wanted, works without battery or with external power supply. This also makes the possibility of use battery as back-up |
| RF_VCC / RF_GND | External module feeding, relying on 5V power supply for hungry modules |
| RF_TX / RF_RX | External module data feeding / receiving, this is the communication link |

As you can see until here, the project was designed to use an uController as bridge, wich connects the data to the transmission <-> or transmission with the data storage.
Faster radios or even better uControllers certainly will improve system's overall speed (such as few LoRa modems (like SX12xx series) with STM32 uController. Maybe is also interesting future tests with BLE (Bluetooth Low Energy) devices. 

The main reason of componnents / modules choice is based on what I had to test and proof the work of basic system in my own lab. As you can see in the .ino or .py programs, the codes are completely portable to any wanted platform. Such as STM32, or even an mBed board, for example. 

Is also possible to observe that even with ESP solution, if speed isn't a problem, interactive plots may be done with a simple code. If you also want to view few videos of the real implementations working, check here: https://tinyurl.com/mwtjrbfp

References:

	https://room-15.github.io/blog/2015/03/26/esp8266-at-command-reference/
	https://docs.espressif.com/projects/esp-at/en/latest/esp32/AT_Command_Set/Wi-Fi_AT_Commands.html
	https://www.electronicshub.org/esp8266-at-commands/
	https://www.espressif.com/sites/default/files/documentation/4b-esp8266_at_command_examples_en.pdf
	https://github.com/beegee-tokyo/SX126x-Arduino#explanation-for-txco-and-antenna-control
