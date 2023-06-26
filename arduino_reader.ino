#include <Wire.h>

int irSensorPrev;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  irSensorPrev = -1;
}

void loop() {
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  delay(100);
}

void receiveEvent() {
  
   int irSensorTriggered = Wire.read();

   if(irSensorTriggered != irSensorPrev){
     Serial.println("sensor: ");
     Serial.print(irSensorTriggered);
     irSensorPrev = irSensorTriggered;
   }
}
