#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "MCP_DAC.h"
#include <EEPROM.h>

#define SCK_PIN 11
#define SDI_PIN 12
#define CS_PIN 13
#define DAC_MAX 4095

#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_G 6 //OE
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_LAT 9 //ST

#define LEDARRAY_D_1 25
#define LEDARRAY_C_1 26
#define LEDARRAY_B_1 27
#define LEDARRAY_A_1 28
#define LEDARRAY_G_1 29 //OE
#define LEDARRAY_DI_1 30
#define LEDARRAY_CLK_1 31
#define LEDARRAY_LAT_1 32 //ST

#define LEDARRAY_D_2 33
#define LEDARRAY_C_2 34
#define LEDARRAY_B_2 35
#define LEDARRAY_A_2 36
#define LEDARRAY_G_2 37 //OE
#define LEDARRAY_DI_2 38
#define LEDARRAY_CLK_2 39
#define LEDARRAY_LAT_2 40 //ST

#define LEDARRAY_D_3 41
#define LEDARRAY_C_3 42
#define LEDARRAY_B_3 43
#define LEDARRAY_A_3 44
#define LEDARRAY_G_3 45 //OE
#define LEDARRAY_DI_3 46
#define LEDARRAY_CLK_3 47
#define LEDARRAY_LAT_3 48 //ST

#define arcadebutton1Pin 23
#define arcadebutton2Pin 24

#define Num_Of_Word 26

//------dot matrix
int arcadebutton1State = 0;
int arcadebutton2State = 0;
uint8_t i1, i2, i1_1,i2_1, i1_2,i2_2, i1_3,i2_3 = 0;
bool savedFirstChar = false;
bool savedSecondChar = false;
bool lockButtons = false;
unsigned char Display_Buffer[2];
unsigned char wordToDisplay[1][32];
unsigned char wordToDisplay_1[1][32];
unsigned char wordToDisplay_2[1][32];
unsigned char wordToDisplay_3[1][32];
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

//------display matrix
Adafruit_7segment matrix0 = Adafruit_7segment();
Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();
Adafruit_7segment matrix3  = Adafruit_7segment();
uint16_t count1, count2, count3 = 0;

//-------motor variables
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

int writeval;
MCP4921 myDAC(SDI_PIN, SCK_PIN);


//------timer (this will be used as user scores)
volatile uint16_t count;

//------main
bool highScore = false;
bool game_started;
int IR_triggered;

//------highscore
bool newHighScoreMaze1 = false;
bool newHighScoreMaze2 = false;
bool newHighScoreMaze3 = false;
byte lowByte, highByte = 0;

ISR(TIMER1_COMPA_vect) {
  sei();
  count++;
  update_timer();
}

void update_timer() {
  matrix0.writeDigitNum(0, (count / 1000));
  matrix0.writeDigitNum(1, (count / 100) % 10);
  matrix0.writeDigitNum(3, (count / 10) % 10, true);
  matrix0.writeDigitNum(4, count % 10);
 
  matrix0.writeDisplay();
}

void read_IR(){
 IR_triggered = Wire.read();

}

void check_second_arduino(){
      Wire.onReceive(read_IR); // function that executes whenever data (IR triggers in this case) is received from writer
}

void motor_control(){
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
/*
  Serial.print("AngleX= ");
  Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("----------------------------");*/

  // MPU x/y axis are 0/360 degrees when lying flat, want to only move the maze when the controller x/y axis is between 90-0 and 360-270 degrees
  // Motor has 0/360 degrees at the bottom.
  // It can rotate from 30 to 330 degrees in the countclock wise direction (300 degree rotation), where 0 volts is 30 degrees and 5 volts is 330 degrees.
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
}

void setup_timer(){
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 6250; // 100ms / 16us = 6250
  TCCR1B = (1 << WGM12) | (1 << CS12);
  TIMSK1 = (1 << OCIE1A);
  sei();
  Serial.println("TIMER1 Setup Finished.");
}

void waitForButtonPress(void) {
  while (!lockButtons) {
    firstLetter();
    secondLetter();
  }
}

// this function sends buffer for dot display from right to left, latches it, and scan the line
void Display(const unsigned char dac[][32])   //dac = matrix of 26 *32
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G, HIGH);   //output enable is high

    Display_Buffer[0] = dac[0][i];    //buffer [0] = col 0,later till 15 (bottom right)
    Display_Buffer[1] = dac[0][i + 16]; //buffer [1] = col 16 ,later till 32 (top right)

    Send(Display_Buffer[1]);  //send buffer[1]
    Send(Display_Buffer[0]);  //send buffer[0]
    //buffer 0 starts from bottom right, buffer 1 starts from top right

    digitalWrite(LEDARRAY_LAT, HIGH);  //latch is high

    digitalWrite(LEDARRAY_LAT, LOW);  //latch is low, not important??
    delayMicroseconds(1);             //bigger value: slower shift + less bright

    Scan_Line(i);           //scan line 0, later till 15


    digitalWrite(LEDARRAY_G, LOW);    //output enable is low, maybe so that outputs are in off state?
    delayMicroseconds(100);;      //bigger value: slower shift
  }
}

void Display_1(const unsigned char dac[][32])   
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G_1, HIGH);   

    Display_Buffer[0] = dac[0][i];    
    Display_Buffer[1] = dac[0][i + 16]; 

    Send_1(Display_Buffer[1]);  
    Send_1(Display_Buffer[0]); 

    digitalWrite(LEDARRAY_LAT_1, HIGH);

    digitalWrite(LEDARRAY_LAT_1, LOW);  
    delayMicroseconds(1);          

    Scan_Line_1(i);    


    digitalWrite(LEDARRAY_G_1, LOW);   
    delayMicroseconds(100);;     
  }
}

void Display_2(const unsigned char dac[][32])   
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G_2, HIGH);   

    Display_Buffer[0] = dac[0][i];    
    Display_Buffer[1] = dac[0][i + 16]; 

    Send_2(Display_Buffer[1]);  
    Send_2(Display_Buffer[0]); 

    digitalWrite(LEDARRAY_LAT_2, HIGH);

    digitalWrite(LEDARRAY_LAT_2, LOW);  
    delayMicroseconds(1);          

    Scan_Line_2(i);    


    digitalWrite(LEDARRAY_G_2, LOW);   
    delayMicroseconds(100);;     
  }
}

void Display_3(const unsigned char dac[][32])   
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G_3, HIGH);   

    Display_Buffer[0] = dac[0][i];    
    Display_Buffer[1] = dac[0][i + 16]; 

    Send_3(Display_Buffer[1]);  
    Send_3(Display_Buffer[0]); 

    digitalWrite(LEDARRAY_LAT_3, HIGH);

    digitalWrite(LEDARRAY_LAT_3, LOW);  
    delayMicroseconds(1);          

    Scan_Line_3(i);    


    digitalWrite(LEDARRAY_G_3, LOW);   
    delayMicroseconds(100);;     
  }
}
//this function scans the line of the matrix, for 16 different cases
//demux 3 to 8, in this program i think it's 4 to 16 (74HC138 datasheet)
//when it is row 0, this function writes to row 0
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

void Scan_Line_1( unsigned char m)
{
  switch (m)
  {
    case 0:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 1:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 2:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 3:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 4:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 5:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 6:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 7:
      digitalWrite(LEDARRAY_D_1, LOW); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 8:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 9:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 10:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 11:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, LOW); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 12:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 13:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, LOW); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    case 14:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, LOW);
      break;
    case 15:
      digitalWrite(LEDARRAY_D_1, HIGH); digitalWrite(LEDARRAY_C_1, HIGH); digitalWrite(LEDARRAY_B_1, HIGH); digitalWrite(LEDARRAY_A_1, HIGH);
      break;
    default : break;
  }
}

void Scan_Line_2( unsigned char m)
{
  switch (m)
  {
    case 0:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 1:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 2:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 3:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 4:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 5:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 6:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 7:
      digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 8:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 9:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 10:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 11:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 12:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 13:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    case 14:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
      break;
    case 15:
      digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
      break;
    default : break;
  }
}

void Scan_Line_3(unsigned char m) {
  switch (m)
  {
    case 0:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 1:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 2:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 3:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 4:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 5:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 6:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 7:
      digitalWrite(LEDARRAY_D_3, LOW); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 8:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 9:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 10:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 11:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, LOW); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 12:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 13:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, LOW); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    case 14:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, LOW);
      break;
    case 15:
      digitalWrite(LEDARRAY_D_3, HIGH); digitalWrite(LEDARRAY_C_3, HIGH); digitalWrite(LEDARRAY_B_3, HIGH); digitalWrite(LEDARRAY_A_3, HIGH);
      break;
    default : break;
  }
}

//this function sends the buffer data (1 byte) bit by bit to display
//74HC595 datasheet
void Send( unsigned char dat)
{
  unsigned char f;
  digitalWrite(LEDARRAY_CLK, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT, LOW);
  delayMicroseconds(1);;

  for ( f = 0 ; f < 8 ; f++ )
  {
    if ( dat & 0x01 ) //if data at current address = 1
    {
      digitalWrite(LEDARRAY_DI, HIGH);  //set data pin high
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
    dat >>= 1;                      //data is shifted to the right by 1

  }
}

void Send_1( unsigned char dat)
{
  unsigned char f;
  digitalWrite(LEDARRAY_CLK_1, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT_1, LOW);
  delayMicroseconds(1);;

  for ( f = 0 ; f < 8 ; f++ )
  {
    if ( dat & 0x01 ) 
    {
      digitalWrite(LEDARRAY_DI_1, HIGH);  
    }
    else
    {
      digitalWrite(LEDARRAY_DI_1, LOW);
    }

    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_1, HIGH);
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_1, LOW);
    delayMicroseconds(1);
    dat >>= 1;                    

  }
}

void Send_2( unsigned char dat)
{
  unsigned char f;
  digitalWrite(LEDARRAY_CLK_2, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT_2, LOW);
  delayMicroseconds(1);;

  for ( f = 0 ; f < 8 ; f++ )
  {
    if ( dat & 0x01 ) 
    {
      digitalWrite(LEDARRAY_DI_2, HIGH); 
    }
    else
    {
      digitalWrite(LEDARRAY_DI_2, LOW);
    }

    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_2, HIGH);
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_2, LOW);
    delayMicroseconds(1);
    dat >>= 1;                      

  }
}

void Send_3( unsigned char dat)
{
  unsigned char f;
  digitalWrite(LEDARRAY_CLK_3, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT_3, LOW);
  delayMicroseconds(1);;

  for ( f = 0 ; f < 8 ; f++ )
  {
    if ( dat & 0x01 ) 
    {
      digitalWrite(LEDARRAY_DI_3, HIGH); 
    }
    else
    {
      digitalWrite(LEDARRAY_DI_3, LOW);
    }

    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_3, HIGH);
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK_3, LOW);
    delayMicroseconds(1);
    dat >>= 1;                  

  }
}

void firstLetter() {
  while (!savedFirstChar) {
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
      savedFirstChar = true;
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
  while (!savedSecondChar) {
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
      savedSecondChar = true;
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

void resetDotMatrix(void) {
  savedFirstChar = false;
  savedSecondChar = false;
  lockButtons = false;
  i1 = 0;
  i2 = 0;
  return;
}

bool checkForHighScore(void) {
  switch (IR_triggered) {
    case 1:
      if (count < count1) {
        newHighScoreMaze1 = true;
        return true;
      }
    case 2:
      if (count < count2) {
        newHighScoreMaze2 = true;
        return true;
      }
    case 3:
      if (count < count3) {
        newHighScoreMaze3 = true;
        return true;
      }
    default: 
      return false;
  }
}

void storeToEEPROM(void) {
  if (newHighScoreMaze1){
    EEPROM.update(0, i1);
    EEPROM.update(1, i2);
    lowByte = (uint8_t) count;
    highByte = (uint8_t) (count>>8) ;
    EEPROM.update(2, lowByte);
    EEPROM.update(3, highByte);
    newHighScoreMaze1 = false;
    }
  else if (newHighScoreMaze2) {
    EEPROM.update(10, i1);
    EEPROM.update(11, i2);
    lowByte = (uint8_t) count;
    highByte = (uint8_t) (count >> 8) ;
    EEPROM.update(12, lowByte);
    EEPROM.update(13, highByte);
    newHighScoreMaze2 = false;
  } 
  else if (newHighScoreMaze3) {
    EEPROM.update(20, i1);
    EEPROM.update(21, i2);
    lowByte = (uint8_t) count;
    highByte = (uint8_t) (count >> 8) ;
    EEPROM.update(22, lowByte);
    EEPROM.update(23, highByte);
    newHighScoreMaze3 = false;
  }
  return;
}

void readFromEEPROM(void) {
  i1_1 = EEPROM.read(0);
  i2_1 = EEPROM.read(1);
  lowByte = EEPROM.read(2);
  highByte = EEPROM.read(3);
  count1 = lowByte + (highByte << 8);

  i1_2 = EEPROM.read(10);
  i2_2 = EEPROM.read(11);
  lowByte = EEPROM.read(12);
  highByte = EEPROM.read(13);
  count2 = lowByte + (highByte << 8);

  i1_3 = EEPROM.read(20);
  i2_3 = EEPROM.read(21);
  lowByte = EEPROM.read(22);
  highByte = EEPROM.read(23);
  count3 = lowByte + (highByte << 8);
}

void displayLeaderBoard(void) {
  for (int i = 0; i < 32; i++) {
    wordToDisplay_1[0][i] = Word1[i1_1][0][i] & Word2[i2_1][0][i];  //display in led matrix 1
    wordToDisplay_2[0][i] = Word1[i1_2][0][i] & Word2[i2_2][0][i];  // display in led matrix 2
    wordToDisplay_3[0][i] = Word1[i1_3][0][i] & Word2[i2_3][0][i];  // display in led matrix 3
  }

  Display_1(wordToDisplay_1); 
  Display_2(wordToDisplay_2);
  Display_3(wordToDisplay_3);

  matrix1.writeDigitNum(0, (count1 / 1000));
  matrix1.writeDigitNum(1, (count1 / 100) % 10);
  matrix1.writeDigitNum(3, (count1 / 10) % 10, true);
  matrix1.writeDigitNum(4, count1 % 10);

  matrix2.writeDigitNum(0, (count2 / 1000));
  matrix2.writeDigitNum(1, (count2 / 100) % 10);
  matrix2.writeDigitNum(3, (count2 / 10) % 10, true);
  matrix2.writeDigitNum(4, count2 % 10);
  
  matrix3.writeDigitNum(0, (count3 / 1000));
  matrix3.writeDigitNum(1, (count3 / 100) % 10);
  matrix3.writeDigitNum(3, (count3 / 10) % 10, true);
  matrix3.writeDigitNum(4, count3 % 10);

  matrix1.writeDisplay();
  matrix2.writeDisplay();
  matrix3.writeDisplay();
  return;
}


void setup() {
  Serial.begin(9600);
  myDAC.begin(CS_PIN);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  matrix0.begin(0x70);
  matrix1.begin(0x73);
  matrix2.begin(0x75);
  matrix3.begin(0x77);
  Serial.println("Matrix Setup Finished.");

  count = 0;
  IR_triggered = -1;
  game_started = false;

  pinMode(LEDARRAY_D, OUTPUT);
  pinMode(LEDARRAY_C, OUTPUT);
  pinMode(LEDARRAY_B, OUTPUT);
  pinMode(LEDARRAY_A, OUTPUT);
  pinMode(LEDARRAY_G, OUTPUT);
  pinMode(LEDARRAY_DI, OUTPUT);
  pinMode(LEDARRAY_CLK, OUTPUT);
  pinMode(LEDARRAY_LAT, OUTPUT);

  pinMode(LEDARRAY_D_1, OUTPUT);
  pinMode(LEDARRAY_C_1, OUTPUT);
  pinMode(LEDARRAY_B_1, OUTPUT);
  pinMode(LEDARRAY_A_1, OUTPUT);
  pinMode(LEDARRAY_G_1, OUTPUT);
  pinMode(LEDARRAY_DI_1, OUTPUT);
  pinMode(LEDARRAY_CLK_1, OUTPUT);
  pinMode(LEDARRAY_LAT_1, OUTPUT);

  pinMode(LEDARRAY_D_2, OUTPUT);
  pinMode(LEDARRAY_C_2, OUTPUT);
  pinMode(LEDARRAY_B_2, OUTPUT);
  pinMode(LEDARRAY_A_2, OUTPUT);
  pinMode(LEDARRAY_G_2, OUTPUT);
  pinMode(LEDARRAY_DI_2, OUTPUT);
  pinMode(LEDARRAY_CLK_2, OUTPUT);
  pinMode(LEDARRAY_LAT_2, OUTPUT);

  pinMode(LEDARRAY_D_3, OUTPUT);
  pinMode(LEDARRAY_C_3, OUTPUT);
  pinMode(LEDARRAY_B_3, OUTPUT);
  pinMode(LEDARRAY_A_3, OUTPUT);
  pinMode(LEDARRAY_G_3, OUTPUT);
  pinMode(LEDARRAY_DI_3, OUTPUT);
  pinMode(LEDARRAY_CLK_3, OUTPUT);
  pinMode(LEDARRAY_LAT_3, OUTPUT);

  pinMode(arcadebutton1Pin, INPUT);
  pinMode(arcadebutton2Pin, INPUT);

  Display(Init_Display);
  Display_1(Init_Display);
  Display_2(Init_Display);
  Display_3(Init_Display);
}

void loop() {
  readFromEEPROM(); 
  displayLeaderBoard(); //TODO: put in sensor while loop, uncomment matrices
  //calls read_IR
  check_second_arduino();
  // Serial.print(IR_triggered);
  // Serial.print(game_started);
  //Serial.print("\n");
  if (IR_triggered == 0 && game_started ==false){ //if start IR is triggered
    Serial.print("im in");
    
    setup_timer();
    Serial.print("still going");
    game_started = true;
    count =0;
}

  while (game_started){
    //-------motor control --------------
    
    motor_control();
    check_second_arduino();
    if(IR_triggered == 4){
      Serial.print("you loser");
      Serial.print(count);


    }
    if (IR_triggered == 1 || IR_triggered == 2 || IR_triggered == 3){//maze 1 complete
      TCCR1B &=~((1<<CS12) | (1<<CS11)|(1<<CS10));
      game_started = false;
      Serial.println("IM HERE");
      highScore = checkForHighScore(); // IMP: using current count, so don't move it around
      if (highScore) {
        //TODO: flash dot matrix + diff LEDs
        Serial.print("YOU GOT HIGH SCORE");
        waitForButtonPress();
        storeToEEPROM(); // IMP: using current i1 and i2 variables, so don't move it around
        
      }
      Serial.print("YOU WON");

      Serial.print(count);
      //leds, update leaderboard, 
      resetDotMatrix(); 

    }
  }
}
