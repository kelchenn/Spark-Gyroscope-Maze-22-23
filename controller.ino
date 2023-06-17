#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "MCP_DAC.h"

Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

#define SCK_PIN 8
#define SDI_PIN 9
#define CS_PIN 10
#define POT_PIN A0
#define DAC_MAX 4095

int writeval;
MCP4921 myDAC(SDI_PIN, SCK_PIN);

volatile uint16_t count;

ISR(TIMER1_COMPA_vect) {
  sei();
  count++;
  update_timer();
}

void update_timer() {
  Serial.println(count);
  matrix1.writeDigitNum(0, (count / 1000));
  matrix1.writeDigitNum(1, (count / 100) % 10);
  matrix1.writeDigitNum(3, (count / 10) % 10, true);
  matrix1.writeDigitNum(4, count % 10);
 
  matrix1.writeDisplay();
}

void setup() {
  myDAC.begin(CS_PIN);
  Wire.begin();

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 6250; // 100ms / 16us = 6250
  TCCR1B = (1 << WGM12) | (1 << CS12);
  TIMSK1 = (1 << OCIE1A);
  sei();
  Serial.println("TIMER1 Setup Finished.");
  
  matrix0.begin(0x70);
  matrix1.begin(0x77);
  Serial.println("Matrix Setup Finished.");
  count = 0;
}
void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  Serial.print("AngleX= ");
  Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");

  // MPU x/y axis are 0/360 degrees when lying flat, want to only move the maze when the controller x/y axis is between 90-0 and 360-270 degrees
  // Motor has 0/360 degrees at the bottom.
  // It can rotate from 30 to 330 degrees in the counterclock wise direction (300 degree rotation), where 0 volts is 30 degrees and 5 volts is 330 degrees.
  // We want the maze to have a max rotation of 45 degrees from the horizontal, so between 135 and 225 degrees.
  // So every 300 degrees / 5 volts = 60 degrees per 1 volt to the motor.
  // DAC_MAX / 5 = 819 = 60 degrees = 1 volt
  // 819 * 0.75 = 614 for 45 degrees
  // DAC_MAX / 2 = 2047.5, which is 180 degrees for the motor, or the maze resting position that we want

  if (y >= 0 && y <= 90) {
    //DAC_MAX/5=819 = 1volt=60deg
    myDAC.analogWrite(map(y, 90, 0, 1461, 2047));
  } else if (y >= 270 && y <= 360) {
    myDAC.analogWrite(map(y, 360, 270, 2048, 2662));
  }
  delay(400);
}
