#include "BeatPattern.hpp"
#include <stdint.h>

/*
 * set bit(s) n of x to beat
 */
inline beat_pattern bit_set(beat_pattern beat, uint8_t n, beat_pattern x) {
  return (beat & ~((uint8_t)3 << n)) | (x << n);
}

BeatPattern::BeatPattern() { }

void BeatPattern::cycleBeat(uint8_t position) {
  beat_pattern mask = 3 << position * 2; // 0b11 in the position of the note
  beat_pattern newbeat = (beat & mask) >> position * 2; // the current value as LSBs
  ++newbeat %= 4;    // incr  & restrict to 0-3
  beat = bit_set(beat, position * 2, newbeat);
  
  // call BeatChanged(position)
}

void BeatPattern::clear() {
  beat = 0;
  // TODO: trigger cleared event to reset all LEDs
}

beat_pattern BeatPattern::get() {
  return beat;
}

