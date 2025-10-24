#include "beat_pattern.h"
#include <stdint.h>

static int rev_g(int);
static int g(int);

beat_pattern cycle_beat(beat_pattern beat, uint8_t position) {
  beat_pattern mask = 3 << position; // 0b11 in the position of the note
  beat_pattern newbeat = (beat & mask) >> position; // the current value as LSBs
  newbeat = rev_g(newbeat);
  ++newbeat %= 4; // incr  & restrict to 0-3
  return g(newbeat); // return after conversion back to graycode
}

// to graycode
static int g(int n) {
  return n ^ (n >> 1);
}
// from graycode
static int rev_g (int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
