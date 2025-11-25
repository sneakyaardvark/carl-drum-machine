#ifndef H_CARL_BEAT_PATTERN
#define H_CARL_BEAT_PATTERN
#include <stdint.h>

typedef uint16_t beat_pattern;

class BeatPattern {
  private:
    beat_pattern beat;

  public:
    BeatPattern();
    void cycleBeat(beat_pattern *beat, uint8_t position);
    void clear();
    beat_pattern get();
};

#endif // !H_CARL_BEAT_PATTERN
