#include <FastLED.h>
#include <climits>
#define DATA_PIN 13
#define NUM_LEDS 30
#define LED_TYPE NEOPIXEL
//simulating win
bool win = true;
//creating array for led manipulation
CRGB leds[NUM_LEDS];
/*
int purp[3] = {129, 2, 129};
int blue[3] = {0, 0, 255};
int green[3] = {123, 245, 2};
int yellow[3] = {248, 248, 7};
int orange[3] = {253, 166, 6};
int red[3] = {255,0,0};
*/
int colors[6][3] = {{129, 2, 129},{0, 0, 255},{123, 245, 2},{248, 248, 7},{253, 166, 6},{255,0,0}};
int moveColorCount = 0;

void setup() {
  // setup an array (led) so we can manipulate it
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (win){
    //if user wins, a set of celebration lighting pattern
   
   //rbg rainbow animation
    for (int i=0;i<NUM_LEDS;i++){
     int color = (i+moveColorCount)%6;
     leds[i] = CRGB(colors[color][0],colors[color][1],colors[color][2]);
   }
    if (moveColorCount < INT_MAX){
      moveColorCount++;
    }else{
      moveColorCount =0; 
    }
    FastLED.show();
    delay(100);
   
  }else{
    //if user loses, a diff set of lighting pattern
   
   //flashing red and black animation
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::Red;
    }
    FastLED.show();
    
    delay(300);
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(100);
  }
}

//simulation  link: https://wokwi.com/projects/350058493201351250

//other animations:
/*
//red drop then red strip
bool staticled = false;
if  (!staticled){
      for (int i=0;i<NUM_LEDS;i++){
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(50);
        leds[i]=CRGB::Black;
        FastLED.show();
        staticled = true;
      }
    }
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::Red;
      
    }
    FastLED.show();
    delay(100);

  }
*/
