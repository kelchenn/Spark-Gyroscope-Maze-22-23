#include <FastLED.h>
#define DATA_PIN 13
#define NUM_LEDS 30
#define LED_TYPE NEOPIXEL
//simulating win
bool win = true;
 
//creating array for led manipulation
CRGB leds[NUM_LEDS];

void setup() {
  // setup an array (led) so we can manipulate it
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (win){
    //if user wins, a set of celebration lighting pattern
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::LawnGreen;
    }
      FastLED.show();
      delay(300);
  }else{
    //if user loses, a diff set of lighting pattern
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::Red;
    }
    FastLED.show();
    }
  delay(300);
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(100);

}

//simulation  link: https://wokwi.com/projects/350058493201351250
