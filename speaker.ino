#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>

SdFat sd;

SFEMP3Shield MP3player;

// These variables are used in the MP3 initialization to set up
// some stereo options:
const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max

int8_t current_track = 0;

void setup() {
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}

void loop() {
  current_track = 1;

  uint8_t result = MP3player.playTrack(current_track);

}

// initSD() initializes the SD card and checks for an error.
void initSD()
{
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

// initMP3Player() sets up all of the initialization for the
// MP3 Player Shield. It runs the begin() function, checks
// for errors, applies a patch if found, and sets the volume/
// stero mode.
void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
