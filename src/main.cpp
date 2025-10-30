#include "config.h"
#include <Arduino.h>
#include <BeatPattern.hpp>

struct carl {
  uint8_t current_voice = 0;
  beat_pattern pattern_mtx[NUM_VOICES][NUM_PATTERNS];
  uint8_t tempo = DEFAULT_TEMPO; 
};

struct carl CARL;

void setup() {
  // MAYBE: sound/logic test on startup

  // core 1: logic
  //          good connections to devices
  //          memory allocation
  //          send some default sound test pattern

  // core 2: playback
  //          init / empty relevant active memory
  //          playback sound test pattern
}

void loop() {
  // core 1: logic
  //          beat pattern changes
  //            MAYBE: "peeking" to know nature of next beats
  //          voice channel changes
  //          tempo changes

  // core 2: playback
  //          sound output
  //            
  //          if digital, effects 
  //            a very basic digital lowpass, highpass,
  //            or reverb could be done at playback

}

