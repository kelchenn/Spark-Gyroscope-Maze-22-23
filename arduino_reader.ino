#include <Wire.h>

int irSensorPrev;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  pinMode(LED_BUILTIN,OUTPUT);  // sets onBoard LED as output
  irSensorPrev = -1;
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
   int irSensorTriggered = Wire.read();

   if(irSensorTriggered != irSensorPrev){
     Serial.println("sensor: ");
     Serial.print(irSensorTriggered);
     irSensorPrev = irSensorTriggered;
   }
}
