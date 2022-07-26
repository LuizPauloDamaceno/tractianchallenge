#include <SoftwareSerial.h>

//environment variables
const int bridgeMode = 9, sRxPin = 10, sTxPin = 11, transferEnd = 13;
long baud = 115200;

String mainSerial, secondarySerial;

#define AP "Closedwrt"
#define APpass "1286432168"

//global definition for softwareSerial
SoftwareSerial swSer (sRxPin, sTxPin);

void setup() {
  //pin definitions:
  pinMode(transferEnd, OUTPUT);
  pinMode(bridgeMode, INPUT);

  //communication link definitions:
  
  Serial.begin (baud);
  swSer.begin (baud);
  Serial.println("ESP configuration starts");

  delay(1000);
  
  //Set ESP parameter
  swSer.println("AT+RST");
  delay(500);
  swSer.println("AT+CWJAP="AP","APpass"");
  delay(500);
  swSer.println("AT+CWMODE=1");
  delay(500);
  swSer.println("AT+CIPMUX=1");
  delay(500);
  swSer.println("AT+CIPSERVER=1");
  delay(500);
  Serial.println("ESP configuration ends");

  Serial.flush();
  swSer.flush();
  Serial.end();
  swSer.end();

  delay(100);
  Serial.begin (baud);
  swSer.begin (baud);

}

void loop() {
  Serial.flush();
  swSer.flush();
  if (Serial.available() > 0) {
    digitalWrite(transferEnd, 1);
    swSer.println("AT+CIPSEND=0,13");
    swSer.flush();
    delay(5);
    mainSerial = Serial.readStringUntil('\n');
    swSer.println(mainSerial);
    }
    digitalWrite(transferEnd, 0);
}
