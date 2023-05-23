#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
Adafruit_7segment matrix3 = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
  matrix0.begin(0x70);
  matrix1.begin(0x73);
  matrix2.begin(0x75);
  matrix3.begin(0x77);
}

void loop() {
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix0.writeDigitNum(0, (counter / 1000));
    matrix0.writeDigitNum(1, (counter / 100) % 10);
    matrix0.writeDigitNum(3, (counter / 10) % 10, true);
    matrix0.writeDigitNum(4, counter % 10);

    matrix1.writeDigitNum(0, ((counter+100) / 1000));
    matrix1.writeDigitNum(1, ((counter+100) / 100) % 10);
    matrix1.writeDigitNum(3, ((counter+100) / 10) % 10, true);
    matrix1.writeDigitNum(4, (counter+100) % 10);

    matrix2.writeDigitNum(0, ((counter+200) / 1000));
    matrix2.writeDigitNum(1, ((counter+200) / 100) % 10);
    matrix2.writeDigitNum(3, ((counter+200) / 10) % 10, true);
    matrix2.writeDigitNum(4, (counter+200) % 10);

    matrix3.writeDigitNum(0, ((counter+300) / 1000));
    matrix3.writeDigitNum(1, ((counter+300) / 100) % 10);
    matrix3.writeDigitNum(3, ((counter+300) / 10) % 10, true);
    matrix3.writeDigitNum(4, (counter+300) % 10);

    matrix0.writeDisplay();
    matrix1.writeDisplay();
    matrix2.writeDisplay();
    matrix3.writeDisplay();
    delay(100);
  }

}
