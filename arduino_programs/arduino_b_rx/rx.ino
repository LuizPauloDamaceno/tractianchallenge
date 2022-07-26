#include <SoftwareSerial.h>

//environment variables
const int bridgeMode = 9, sRxPin = 10, sTxPin = 11, transferEnd = 13;
long baud = 57600;
String mainSerial; 

//global definition for softwareSerial
SoftwareSerial swSer (sRxPin, sTxPin);

void setup() {
  //pin definitions:
  pinMode(transferEnd, OUTPUT);
  pinMode(bridgeMode, INPUT);

  //communication link definitions:
  
  Serial.begin (baud);
  swSer.begin (baud);
}

void loop() {
    if (swSer.available() > 0) {
      digitalWrite(transferEnd, 1);
      mainSerial = swSer.readStringUntil('\n');
      Serial.println(mainSerial);
      swSer.flush();
      Serial.end();
      swSer.flush();
      Serial.end();
      digitalWrite(transferEnd, 0);
      swSer.begin(baud);
      Serial.begin(baud);
    }
}
