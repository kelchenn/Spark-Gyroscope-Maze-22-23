#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

/****START OF GLOBAL VARIABLES****/

// seven segment displays
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
Adafruit_7segment matrix3 = Adafruit_7segment();

/****END OF GLOBAL VARIABLES****/

/****START OF FUNCTION PROTOTYPES****/

void timer(Adafruit_7segment matrix);
void sectionOne();
void sectionTwo();
void sectionThree();
void leaveEarly()
void inputInitials()

/****END OF FUNCTION PROTOTYPES****/

/****START OF FUNCTION IMPLEMENTATIONS****/

void timer(Adafruit_7segment matrix) {
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000));
    matrix.writeDigitNum(1, (counter / 100) % 10);
    matrix.writeDigitNum(3, (counter / 10) % 10, true);
    matrix.writeDigitNum(4, counter % 10);

    matrix.writeDisplay();
    delay(100);
  }
}

// gameplay for maze section one
void sectionOne() {
  // start timer
  // allow controller to move

  // sensors for leave early and finish game holes waiting to detect the ball
  // if they detect the ball, stop the timer and go to winGame() or leaveEarly()
  
}

// gameplay for maze section two
void sectionTwo() {
  
  
}

// gameplay for maze section three
void sectionThree() {
  
  
}

// when the user finishes the game
void winGame() {
  // play lights animation
  // check if they have a highscore, if yes go to inputInitials()
  
}

// when the user leaves the game early
void leaveEarly() {
  
  
}

// when the user gets a highscore
void inputInitials() {
  
  
}

/****END OF FUNCTION IMPLEMENTATIONS****/

void setup() {
  Serial.begin(9600);

  // sensors
  pinMode(IRSensor, INPUT);// set pin as input to receive info on sensor detection
  pinMode(LED, OUTPUT);// to light up LED if something is detected
  
  // seven segment displays
  matrix0.begin(0x70);
  matrix1.begin(0x73);
  matrix2.begin(0x75);
  matrix3.begin(0x77);
}

void loop() {

  // sensor waiting to detect something
  int detect = analogRead(IRSensor);// read ball status and store it into "detect"

  // if a sensor for one of the maze sections detects the ball, go to that section's game loop
  if(detect == LOW){ 
    

  }
}
