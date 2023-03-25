/****START OF CONSTANTS AND LIBRARIES****/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// dot matrix displays
#define Num_Of_Word 26

/****END OF CONSTANTS AND LIBRARIES****/

/****START OF PIN DECLARATIONS****/
// dot matrix displays
#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_G 6 //OE
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_LAT 9 //ST
#define arcadebutton1Pin 23
#define arcadebutton2Pin 24
#define IRSENSOR1 A3;
#define IRSENSOR2 A4;
#define IRSENSOR3 A5;
#define IRSENSOR4 A6;
#define IRSENSOR5 A7;


/****END OF PIN DECLARATIONS****/

/****START OF GLOBAL VARIABLES****/

// MPU 
const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

//gameplay
int state; 
//timing
unsigned long finishTime[3];  //time when the ball reaches end of each section, resets each round
unsigned long fastestTime[3];

// seven segment displays
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
Adafruit_7segment matrix3 = Adafruit_7segment();

//dot matrix displays
unsigned char Display_Buffer[2];
const unsigned char  Word1[Num_Of_Word][1][32] =
{
  //A
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xCF, 0xF7, 0xCF, 0x3F, 0xFF
  },//B
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0x77, 0x77, 0x77, 0x07, 0xFF                                               ,
  },//C
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xEF, 0xEF, 0xEF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF7, 0xF7, 0xF7, 0x0F, 0xFF
  },//D
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xF7, 0x07, 0xFF
  },//E
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xEE, 0xEE, 0xEE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF
  },//F
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF
  },//G
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xEE, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF
  },//H
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF
  },//I
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF
  },//J
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },//K
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF7, 0xF9, 0xFE, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0x07, 0xFF
  },//L
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF
  },//M
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xCF, 0x9F, 0x9F, 0xCF, 0x07, 0xFF                                                                                                
  },//N
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xF3, 0xFC, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0x3F, 0xCF, 0x07, 0xFF                                                
  },//O
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xEF, 0x1F, 0xFF                                                                                                
  },//P
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x77, 0x77, 0x77, 0x07, 0xFF                                                                                                                                               
  },//Q
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE8, 0xF7, 0xEB, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xEF, 0x1F, 0xFF                                                
  },//R
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF6, 0xFA, 0xFC, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF7, 0xF7, 0xF7, 0x07, 0xFF                                                
  },//S
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0xEE, 0xEE, 0xEE, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF7, 0xF7, 0xF7, 0x0F, 0xFF                                                
  },//T
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0x07, 0xF7, 0xF7, 0xFF                                                
  },//U
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xEF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF                                                
  },//V
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF                                                
  },//W
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xE7, 0xF9, 0xF9, 0xE7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF                                                                                                                                                                                                
  },//X
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xF9, 0xFE, 0xF9, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0x9F, 0x7F, 0x9F, 0xE7, 0xFF                                                
  },
  //Y
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xBF, 0x7F, 0xBF, 0xC7, 0xFF                                                
  },//Z
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xEF, 0xEE, 0xE9, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0x97, 0x77, 0xF7, 0xF7, 0xFF                                                
  }
};

const unsigned char  Word2[Num_Of_Word][1][32] =
{
  //A
  { 0xFF, 0xFF, 0xE0, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xCF, 0xF7, 0xCF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //B
  { 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0x77, 0x77, 0x77, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //C
  { 0xFF, 0xFF, 0xF7, 0xEF, 0xEF, 0xEF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF7, 0xF7, 0xF7, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //D
  { 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //E
  { 0xFF, 0xFF, 0xEF, 0xEE, 0xEE, 0xEE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //F
  { 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //G
  { 0xFF, 0xFF, 0xE0, 0xEE, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0xF7, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //H
  { 0xFF, 0xFF, 0xE0, 0xFE, 0xFE, 0xFE, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //I
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //J
  { 0xFF, 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //K
  { 0xFF, 0xEF, 0xF7, 0xF9, 0xFE, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //L
  { 0xFF, 0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  },
  //M
  { 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xCF, 0x9F, 0x9F, 0xCF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //N
  { 0xFF, 0xE0, 0xF3, 0xFC, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0x3F, 0xCF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //O
  { 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xEF, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //P
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x77, 0x77, 0x77, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //Q
  { 0xFF, 0xFF, 0xE8, 0xF7, 0xEB, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xEF, 0xF7, 0xEF, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //R
  { 0xFF, 0xFF, 0xEF, 0xF6, 0xFA, 0xFC, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF7, 0xF7, 0xF7, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //S
  { 0xFF, 0xFF, 0xF1, 0xEE, 0xEE, 0xEE, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xF7, 0xF7, 0xF7, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //T
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF7, 0x07, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //U
  { 0xFF, 0xFF, 0xF0, 0xEF, 0xEF, 0xEF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //V
  { 0xFF, 0xFF, 0xF8, 0xF7, 0xEF, 0xF7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //W
  { 0xFF, 0xF8, 0xE7, 0xF9, 0xF9, 0xE7, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //X
  { 0xFF, 0xFF, 0xE7, 0xF9, 0xFE, 0xF9, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0x9F, 0x7F, 0x9F, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //Y
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xBF, 0x7F, 0xBF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                                
  },
  //Z
  { 0xFF, 0xFF, 0xEF, 0xEF, 0xEE, 0xE9, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0x97, 0x77, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF                                               
  }
};
const unsigned char  Init_Display[1][32] = //all on
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
int arcadebutton1State = 0;
int arcadebutton2State = 0;
int i1 = 0;   //index first letter
int i2 = 0;   //index second letter
bool savedFirst = false;
bool savedSecond = false;
bool lockButtons = false;

/****END OF GLOBAL VARIABLES****/

/****START OF FUNCTION PROTOTYPES****/

int detectSection();
void timer(Adafruit_7segment matrix);
void sectionOne();
void sectionTwo();
void sectionThree();
void leaveEarly();
void inputInitials();
void Display(const unsigned char data[][32]);
void Send( unsigned char data);
void Scan_Line(unsigned char m);
void firstLetter();
void secondLetter();

/****END OF FUNCTION PROTOTYPES****/

/****START OF FUNCTION IMPLEMENTATIONS****/

void MPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ);
  
  //equation for temperature in degrees C from datasheet
  Serial.print("Temperature: "); Serial.print(Tmp / 340.00 + 36.53); Serial.println(" C ");

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
}

int detectSection() {
  
  for(int i=A3;i<A8;i++){
    // read ball status and store it into "detect"
    int detect = analogRead(i);
    Serial.println(i);
    if(detect <200){ //ball detected
      if(i==A3){
        Serial.println("end section 1")
        return 1;
      }else if(i==A4){
        Serial.println("end section 2")
        return 2;
      }else if(i==A5){
        Serial.println("end section 3")
        return 3;
      }else if(i==A6){
        Serial.println("early ending")
        return -1;
      }else if(i==A7){
        Serial.println("start")
        return 10
      }
  }
  return 0;
}
  //TO DO: write function to detect which IR sensor is triggered and return the section number as an int
}
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
  // TODO: call timer, program finishTime[state] and fastestTime [state]
  
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
  if (finishTime[state] > fastestTime [state]) {
    fastestTime[state] = fastestTime [state];
    inputInitials();
  }
    
}

// when the user leaves the game early
void leaveEarly() {
  
  
}

// when the user gets a highscore
void inputInitials() {
    while (!lockButtons) {
    firstLetter();
    secondLetter();
    }
    Display(Word1[i1]);
    Display(Word2[i2]);
}

void Display(const unsigned char dac[][32])  
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G, HIGH);   

    Display_Buffer[0] = dac[0][i];    
    Display_Buffer[1] = dac[0][i + 16]; 

    Send(Display_Buffer[1]);
    Send(Display_Buffer[0]);  

    digitalWrite(LEDARRAY_LAT, HIGH);  

    digitalWrite(LEDARRAY_LAT, LOW);  
    delayMicroseconds(1);           

    Scan_Line(i);          

    digitalWrite(LEDARRAY_G, LOW);    
    delayMicroseconds(100);;     
  }
}

void Scan_Line( unsigned char m)
{
  switch (m)
  {
    case 0:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 1:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 2:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 3:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 4:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 5:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 6:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 7:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 8:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 9:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 10:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 11:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 12:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 13:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 14:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 15:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    default : break;
  }
}

void Send( unsigned char dat)
{
  unsigned char f;
  digitalWrite(LEDARRAY_CLK, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT, LOW);
  delayMicroseconds(1);;

  for ( f = 0 ; f < 8 ; f++ )
  {
    if ( dat & 0x01 ) 
    {
      digitalWrite(LEDARRAY_DI, HIGH);  
    }
    else
    {
      digitalWrite(LEDARRAY_DI, LOW);
    }

    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, LOW);
    delayMicroseconds(1);
    dat >>= 1;                    

  }
}

void firstLetter() {
  while (!savedFirst) {
    Display(Word1[i1]);
    Display(Word2[i2]);
    arcadebutton1State = digitalRead(arcadebutton1Pin);
    arcadebutton2State = digitalRead(arcadebutton2Pin);
    if (arcadebutton1State == HIGH) {
      i1++;     //increment first letter
      if (i1 == Num_Of_Word) i1 = 0;
      while (arcadebutton1State == HIGH) {
        Display(Word1[i1]);
        Display(Word2[i2]);
        arcadebutton1State = digitalRead(arcadebutton1Pin);
      }
    }
    else if (arcadebutton2State == HIGH) {
      savedFirst = true;
      while (arcadebutton2State == HIGH) {
        Display(Word1[i1]);
        Display(Word2[i2]);
        arcadebutton2State = digitalRead(arcadebutton2Pin);
      }
    }
  }
  return;
}

void secondLetter() {
  while (!savedSecond) {
    Display(Word1[i1]);
    Display(Word2[i2]);
    arcadebutton1State = digitalRead(arcadebutton1Pin);
    arcadebutton2State = digitalRead(arcadebutton2Pin);
    if (arcadebutton1State == HIGH) {
      i2++;   
      if (i2 == Num_Of_Word) i2 = 0;
      while (arcadebutton1State == HIGH) {
        Display(Word1[i1]);
        Display(Word2[i2]);
        arcadebutton1State = digitalRead(arcadebutton1Pin);
      }
    }
    else if (arcadebutton2State == HIGH) {
      savedSecond = true;
      lockButtons = true;
      while (arcadebutton2State == HIGH) {
        Display(Word1[i1]);
        Display(Word2[i2]);
        arcadebutton2State = digitalRead(arcadebutton2Pin);
      }
    }
  }
  return;
}

/****END OF FUNCTION IMPLEMENTATIONS****/

void setup() {
  Serial.begin(9600);

  // sensors
  pinMode(IRSENSOR1, INPUT);
  pinMode(IRSENSOR2, INPUT);
  pinMode(IRSENSOR3, INPUT);
  pinMode(IRSENSOR4, INPUT);
  pinMode(IRSENSOR5, INPUT);
  pinMode(LED, OUTPUT);// to light up LED if something is detected
  
  // seven segment displays
  matrix0.begin(0x70);
  matrix1.begin(0x73);
  matrix2.begin(0x75);
  matrix3.begin(0x77);

  //dot matrix displays
  pinMode(LEDARRAY_D, OUTPUT);
  pinMode(LEDARRAY_C, OUTPUT);
  pinMode(LEDARRAY_B, OUTPUT);
  pinMode(LEDARRAY_A, OUTPUT);
  pinMode(LEDARRAY_G, OUTPUT);
  pinMode(LEDARRAY_DI, OUTPUT);
  pinMode(LEDARRAY_CLK, OUTPUT);
  pinMode(LEDARRAY_LAT, OUTPUT);
  pinMode(arcadebutton1Pin, INPUT);
  pinMode(arcadebutton2Pin, INPUT);
  Display(Init_Display);

  //MPU 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  // Serial.begin(9600);

}

void loop() {
    //TO DO: make a function that wait for user to start game in detectSection()
    // if a sensor for one of the maze sections detects the ball, go to that section's game loop
    state = detectSection();

    switch (state) {
      case 1:
        sectionOne();
        break;
      case 2:
        sectionTwo();
        break;
      case 3:
        sectionThree();
        break;
    }

  // MPU 
  MPU();
     
}
