#include "BeatPattern.hpp"
#include <stdint.h>

BeatPattern::BeatPattern() { }

void BeatPattern::cycleBeat(beat_pattern* beat, uint8_t position) {
  beat_pattern mask = 3 << (2 * position); // 0b11 in the position of the note
  beat_pattern newbeat = (*beat & mask) >> (2 * position); // the current value as LSBs
  ++newbeat %= 4;    // incr  & restrict to 0-3
  *beat &= newbeat << (2 * position);
  // call BeatChanged(position)
}

void BeatPattern::clear() {
  beat = 0;
  // call ClearPattern(patternID)
}

beat_pattern BeatPattern::get() {
  return beat;
}

