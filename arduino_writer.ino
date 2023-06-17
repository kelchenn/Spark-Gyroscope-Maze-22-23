#include <Wire.h>

#define IRSENSOR0 A0
#define IRSENSOR1 A1

int irsensorTriggered;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin(); // join i2c bus (address optional for writer)
  pinMode(IRSENSOR0, INPUT);
  pinMode(IRSENSOR1, INPUT);
}

void loop() {
  bool trigger = readSensor();
  if (trigger) {
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(irsensorTriggered); 
    Wire.endTransmission();    // stop transmitting
  }
 
}

/* read sensor */
bool readSensor() {

  int detect = analogRead(IRSENSOR0);

  if (detect < 200) { // ball detected
    return true;
    irsensorTriggered = 0;
  } 

  detect = analogRead(IRSENSOR1);

  if (detect < 200) { // ball detected
    return true;
    irsensorTriggered = 1;
  } 

  return false;
}
