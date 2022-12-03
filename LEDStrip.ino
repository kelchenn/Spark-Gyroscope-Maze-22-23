#include <FastLED.h>
#define DATA_PIN 13
#define NUM_LEDS 30
#define LED_TYPE NEOPIXEL

//creating array for led manipulation
CRGB leds[NUM_LEDS];

void setup() {
  // setup an array (led) so we can manipulate it
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 
  
}

void loop() {
  // red and green flashing
  for (int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB::Red;

   }
    FastLED.show();
   delay(300);
   for (int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB::CRGB::LawnGreen;
   
   }
    FastLED.show();
    delay(300);
}
