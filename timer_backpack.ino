#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix0.begin(0x70);
  matrix1.begin(0x77);
}

void loop() {
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000));
    matrix.writeDigitNum(1, (counter / 100) % 10);
    matrix.writeDigitNum(3, (counter / 10) % 10, true);
    matrix.writeDigitNum(4, counter % 10);

    matrix0.writeDisplay();
    delay(100);
  }

  for (uint16_t counter = 100; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000));
    matrix.writeDigitNum(1, (counter / 100) % 10);
    matrix.writeDigitNum(3, (counter / 10) % 10, true);
    matrix.writeDigitNum(4, counter % 10);

    matrix1.writeDisplay();
    delay(100);
  }
}
