#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  pinMode(LED_BUILTIN,OUTPUT);  // sets onBoard LED as output
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
   bool trigger = Wire.read(); // receive a character
   if(trigger){
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
   }
   if(!trigger){
     digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
   }
}
