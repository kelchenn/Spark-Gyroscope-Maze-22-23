#include <Wire.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin(); // join i2c bus (address optional for writer)
  pinMode(A0, INPUT);
}

void loop() {
  int detect = analogRead(A0);
  bool trigger = readSensor(detect);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(trigger);        // sends the given value
  Wire.endTransmission();    // stop transmitting
  delay(500);
}

/* read sensor */
bool readSensor(int detect) {
  if (detect < 200) { // ball detected
    return true;
  } 

  return false;
}
