#include "BeatPattern.hpp"
#include <stdint.h>


void BeatPattern::cycleBeat(beat_pattern* beat, uint8_t position) {
  beat_pattern mask = 3 << position; // 0b11 in the position of the note
  beat_pattern newbeat = (*beat & mask) >> position; // the current value as LSBs
  ++newbeat %= 4;    // incr  & restrict to 0-3
  *beat &= newbeat << position;
  // call BeatChanged(position)
}

void BeatPattern::clear() {
  beat = 0;
  // TODO: trigger cleared event to reset all LEDs
}

beat_pattern BeatPattern::get() {
  return beat;
}

