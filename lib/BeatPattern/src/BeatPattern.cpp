#include "BeatPattern.hpp"
#include <string.h>
#include <stdint.h>

BeatPattern::BeatPattern() {
  memset(beats, 0, 8);
}

void BeatPattern::cycleBeat(uint8_t position) {
  // 0 <= pos < 8
  ++beats[position] %= 4;
  onBeatChangedCallback(position, beats[position]);
}

bool BeatPattern::isBeatOn(uint8_t position) {
  // 0 <= pos < 16
  uint8_t qn_pos = position / 2; // get the quarter note pos, i.e. map 0,1->0, 2,3->1, etc.
  return beats[qn_pos] == (qn_pos % 2) + 1;
}

void BeatPattern::clear() {
  for (int i = 0; i < 8; i++) {
    beats[i] = 0;
    onBeatChangedCallback(i, 0);
  }
}

beat_pattern BeatPattern::get() {
  return beats;
}

void BeatPattern::setOnBeatChanged(void (*callback)(uint8_t position, uint8_t state)) {
  onBeatChangedCallback = callback;
}
