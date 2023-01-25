#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x77); // for arduino uno
  // matrix.begin(0x70); // for arduino mega
}

void loop() {
  uint16_t blinkcounter = 0;
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000));
    matrix.writeDigitNum(1, (counter / 100) % 10);
    matrix.writeDigitNum(3, (counter / 10) % 10, true);
    matrix.writeDigitNum(4, counter % 10);

    matrix.writeDisplay();
    delay(100);
  }
}
