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

}

void loop() {

}

