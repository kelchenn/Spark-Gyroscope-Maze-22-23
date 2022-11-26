// Based on a project posted https://github.com/wayoda/LedControl
#include "LedControl.h"

/*
 This simulator is with a single MAX7219.
 What we're using is LEDMX-001616
 with these pins instead: A, B, C, D, OE, D-I, D_O, ST, CLK
 But I'm still not sure how to use them, so I'll simulate an animation from A-Z
 using this matrix available on wokwi.

 Now we need a LedControl to work with.
 */
#define dataPin 12
#define clkPin 11
#define csPin 10
#define numDevices 1  
LedControl lc=LedControl(dataPin, clkPin, csPin, numDevices);

//wait a bit between updates of the display
unsigned long delaytime=600;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


//This method will display the characters A-Z one after the other on the matrix. 
 
void writeAlphabet() {
  /* here is the data for the characters */

  // on matrix, this bytes are read from right to left, so it may need to change
  byte A[8]={B00111000,B01000100,B01000100,B01000100,B01111100,B01000100,B01000100,B01000100};
  byte B[8]={B01111000,B01000100,B01000100,B01111000,B01000100,B01000100,B01111000,B00000000};  
  byte C[8]={B00000000,B00111100,B01000000,B01000000,B01000000,B01000000,B00111100,B00000000};
  byte D[8]={B00000000,B01111000,B01000100,B01000100,B01000100,B01000100,B01111000,B00000000};
  byte E[8]={B00000000,B01111100,B01000000,B01000000,B01111100,B01000000,B01000000,B01111100};     
  byte F[8]={B00000000,B01111100,B01000000,B01000000,B01111100,B01000000,B01000000,B01000000};
  byte G[8]={B00000000,B00111100,B01000000,B01000000,B01000000,B01001110,B01000010,B00111110};  

  //set row parameters:int addr, int row, byte value
  
  /* Letter A */
  //i.e. this method will set first row of matrix with A[0]
  for (int i=0; i<8; i++){
  lc.setRow(0,i,A[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////

  /* Letter B*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,B[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////


  /* Letter C*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,C[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////

  /* Letter D*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,D[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter J///////

  /* Letter E*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,E[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////

  /* Letter F*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,F[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////

  /* Letter G*/
  for (int i=0; i<8; i++){
  lc.setRow(0,i,G[i]);

  }
   
  delay(delaytime);
  for(int i=0; i<8; i++){
      lc.setRow(0,i,0);// this is for blank
  }  
/////////////// END of Letter///////


}


void loop() { 
  writeAlphabet();

}