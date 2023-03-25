#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include "Adafruit_LEDBackpack.h"
#include <stdio.h>
#define IRSENSOR1 A3
#define IRSENSOR2 A4
#define IRSENSOR3 A5
#define IRSENSOR4 A6
#define IRSENSOR5 A7
#define ENDEARLYPIN  2
#define FINISHPIN  3

/*
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
*/
//int LED = 13;
void setup() {
 Serial.begin(9600);
// set pin as input to receive info on SENSOR detection
 pinMode(IRSENSOR1, INPUT);
 pinMode(IRSENSOR2, INPUT);
 pinMode(IRSENSOR3, INPUT);
 pinMode(IRSENSOR4, INPUT);
 pinMode(IRSENSOR5, INPUT);
 pinMode(INTERRUPTPIN, OUTPUT);
 attachInterrupt(digitalPinToInterrupt(2), endEarly, RISING);
 attachInterrupt(digitalPinToInterrupt(3), finish, RISING);
/*
   // set up 7 seg displays
  matrix0.begin(0x70);
  matrix1.begin(0x73);
  matrix2.begin(0x77);
  */
}

int detectSection() {
  for(int i=57;i<62;i++){
    // read ball status and store it into "detect"
    int detect = analogRead(i);
    Serial.println(i);
    if(detect <200){ //ball detected
      if(i==A3){
        Serial.println("end section 1");
        digitalWrite(3, HIGH);
        return 1;
      }else if(i==A4){
        Serial.println("end section 2");
        digitalWrite(3, HIGH);
        return 2;
      }else if(i==A5){
        Serial.println("end section 3");
        digitalWrite(3, HIGH);
        return 3;
      }else if(i==A6){
        Serial.println("early ending");
        digitalWrite(2, HIGH);
        return -1;
      }else if(i==A7){
        Serial.println("start");
        return 10;
      }
  }
}
  //TO DO: write function to detect which IR sensor is triggered and return the section number as an int
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    return 0;

}

void endEarly(){
  //haha loser, BEGIN LOSER LED (true  loser boolean?)
  Serial.println("INTERRUPT: END EARLY");
  delay(500);
}

void finish(){
  //celebrate wohoo, BEGIN WINNER LED (true  winner boolean?)
  Serial.println("INTERRUPT: FINISHED MAZE");
  delay(500);
}

/*

void segDisplay(Adafruit_7segment matrix) {
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000));
    matrix.writeDigitNum(1, (counter / 100) % 10);
    matrix.writeDigitNum(3, (counter / 10) % 10, true);
    matrix.writeDigitNum(4, counter % 10);

    matrix.writeDisplay();
    delay(100);
  }  
  
}
*/

void loop() {
  int res = detectSection();
}
  
