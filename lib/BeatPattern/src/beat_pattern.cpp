#include "beat_pattern.h"
#include <stdint.h>

static int fromGrayCode(int);
static int toGrayCode(int);

beat_pattern cycleBeat(beat_pattern beat, uint8_t position) {
  beat_pattern mask = 3 << position; // 0b11 in the position of the note
  beat_pattern newbeat = (beat & mask) >> position; // the current value as LSBs
  newbeat = fromGrayCode(newbeat);
  ++newbeat %= 4;    // incr  & restrict to 0-3
  return toGrayCode(newbeat); // return after conversion back to graycode
}

// to graycode
static int toGrayCode(int n) { return n ^ (n >> 1); }
// from graycode
static int fromGrayCode(int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
