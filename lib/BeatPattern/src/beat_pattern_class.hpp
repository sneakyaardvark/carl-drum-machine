#include <stdint.h>
class BeatPattern {
private:
  uint16_t pattern;

public:
  void cycleBeat(uint8_t position);
};
