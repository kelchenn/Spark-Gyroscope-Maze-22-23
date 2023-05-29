
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>
//IO
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
#define LEDARRAY_G_1 29
#define LEDARRAY_DI_1 30
#define LEDARRAY_CLK_1 31
#define LEDARRAY_LAT_1 32 //ST

// #define LEDARRAY_D_2 33
// #define LEDARRAY_C_2 34
// #define LEDARRAY_B_2 35
// #define LEDARRAY_A_2 36
// #define LEDARRAY_G_2 37
// #define LEDARRAY_DI_2 38
// #define LEDARRAY_CLK_2 39
// #define LEDARRAY_LAT_2 40 //ST

#define arcadebutton1Pin 23
#define arcadebutton2Pin 24

#define Num_Of_Word 26
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
int i1, i2, i1_1,i2_1 = 0;
bool savedFirst, savedFirst_1 = false;
bool savedSecond, savedSecond_1 = false;
bool lockButtons, lockButtons_1 = false;

// this function sends buffer for dot display from right to left, latches it, and scan the line
void Display(const unsigned char dac[][32])   //dac = matrix of 26 *32 = 0
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

// this function sends buffer for dot display from right to left, latches it, and scan the line
void Display_1(const unsigned char dac[][32])   //dac = matrix of 26 *32 = 0
{
  unsigned char i;


  for ( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G_1, HIGH);   //output enable is high

    Display_Buffer[0] = dac[0][i];    //buffer [0] = col 0,later till 15 (bottom right)
    Display_Buffer[1] = dac[0][i + 16]; //buffer [1] = col 16 ,later till 32 (top right)

    Send_1(Display_Buffer[1]);  //send buffer[1]
    Send_1(Display_Buffer[0]);  //send buffer[0]
    //buffer 0 starts from bottom right, buffer 1 starts from top right

    digitalWrite(LEDARRAY_LAT_1, HIGH);  //latch is high

    digitalWrite(LEDARRAY_LAT_1, LOW);  //latch is low, not important??
    delayMicroseconds(1);             //bigger value: slower shift + less bright

    Scan_Line_1(i);           //scan line 0, later till 15


    digitalWrite(LEDARRAY_G_1, LOW);    //output enable is low, maybe so that outputs are in off state?
    delayMicroseconds(100);;      //bigger value: slower shift
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


// void Scan_Line_2( unsigned char m)
// {
//   switch (m)
//   {
//     case 0:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 1:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 2:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 3:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 4:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 5:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 6:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 7:
//       digitalWrite(LEDARRAY_D_2, LOW); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 8:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 9:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 10:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 11:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, LOW); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 12:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 13:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, LOW); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     case 14:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, LOW);
//       break;
//     case 15:
//       digitalWrite(LEDARRAY_D_2, HIGH); digitalWrite(LEDARRAY_C_2, HIGH); digitalWrite(LEDARRAY_B_2, HIGH); digitalWrite(LEDARRAY_A_2, HIGH);
//       break;
//     default : break;
//   }
// }

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
    if ( dat & 0x01 ) //if data at current address = 1
    {
      digitalWrite(LEDARRAY_DI_1, HIGH);  //set data pin high
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
    dat >>= 1;                      //data is shifted to the right by 1

  }
}

// void Send_2( unsigned char dat)
// {
//   unsigned char f;
//   digitalWrite(LEDARRAY_CLK_2, LOW);
//   delayMicroseconds(1);;
//   digitalWrite(LEDARRAY_LAT_2, LOW);
//   delayMicroseconds(1);;

//   for ( f = 0 ; f < 8 ; f++ )
//   {
//     if ( dat & 0x01 ) //if data at current address = 1
//     {
//       digitalWrite(LEDARRAY_DI_2, HIGH);  //set data pin high
//     }
//     else
//     {
//       digitalWrite(LEDARRAY_DI_2, LOW);
//     }

//     delayMicroseconds(1);
//     digitalWrite(LEDARRAY_CLK_2, HIGH);
//     delayMicroseconds(1);
//     digitalWrite(LEDARRAY_CLK_2, LOW);
//     delayMicroseconds(1);
//     dat >>= 1;                      //data is shifted to the right by 1

//   }
// }

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

void firstLetter_1() {
  while (!savedFirst_1) {
    Display_1(Word1[i1_1]);
    Display_1(Word2[i2_1]);
    arcadebutton1State = digitalRead(arcadebutton1Pin);
    arcadebutton2State = digitalRead(arcadebutton2Pin);
    if (arcadebutton1State == HIGH) {
      i1_1++;     //increment first letter
      if (i1_1 == Num_Of_Word) i1_1 = 0;
      while (arcadebutton1State == HIGH) {
        Display_1(Word1[i1_1]);
        Display_1(Word2[i2_1]);
        arcadebutton1State = digitalRead(arcadebutton1Pin);
      }
    }
    else if (arcadebutton2State == HIGH) {
      savedFirst_1 = true;
      while (arcadebutton2State == HIGH) {
        Display_1(Word1[i1_1]);
        Display_1(Word2[i2_1]);
        arcadebutton2State = digitalRead(arcadebutton2Pin);
      }
    }
  }
  return;
}

void secondLetter_1() {
  while (!savedSecond_1) {
    Display_1(Word1[i1_1]);
    Display_1(Word2[i2_1]);
    arcadebutton1State = digitalRead(arcadebutton1Pin);
    arcadebutton2State = digitalRead(arcadebutton2Pin);
    if (arcadebutton1State == HIGH) {
      i2_1++;   
      if (i2_1 == Num_Of_Word) i2_1 = 0;
      while (arcadebutton1State == HIGH) {
        Display_1(Word1[i1_1]);
        Display_1(Word2[i2_1]);
        arcadebutton1State = digitalRead(arcadebutton1Pin);
      }
    }
    else if (arcadebutton2State == HIGH) {
      savedSecond_1 = true;
      lockButtons_1 = true;
      while (arcadebutton2State == HIGH) {
        Display_1(Word1[i1_1]);
        Display_1(Word2[i2_1]);
        arcadebutton2State = digitalRead(arcadebutton2Pin);
      }
    }
  }
  return;
}
void setup()
{
  Serial.begin(9600);

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

  // pinMode(LEDARRAY_D_2, OUTPUT);
  // pinMode(LEDARRAY_C_2, OUTPUT);
  // pinMode(LEDARRAY_B_2, OUTPUT);
  // pinMode(LEDARRAY_A_2, OUTPUT);
  // pinMode(LEDARRAY_G_2, OUTPUT);
  // pinMode(LEDARRAY_DI_2, OUTPUT);
  // pinMode(LEDARRAY_CLK_2, OUTPUT);
  // pinMode(LEDARRAY_LAT_2, OUTPUT);

  pinMode(arcadebutton1Pin, INPUT);
  pinMode(arcadebutton2Pin, INPUT);
  Display(Init_Display);
  Display_1(Init_Display);
}

  void loop()
{
  while (!lockButtons) {
    firstLetter();
    secondLetter();
  }
  while (!lockButtons_1) {
    firstLetter_1();
    secondLetter_1();
  }
  Display(Word1[i1]);
  Display(Word2[i2]);
  Display_1(Word1[i1_1]);
  Display_1(Word2[i2_1]);
}

