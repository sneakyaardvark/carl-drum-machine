#ifndef H_CARL_BEAT_PATTERN
#define H_CARL_BEAT_PATTERN
#include <stdint.h>

typedef uint8_t *beat_pattern;

class BeatPattern {
  private:
    uint8_t beats[8];
    void (*onBeatChangedCallback)(uint8_t position, uint8_t state) = nullptr;

  public:
    BeatPattern();
    bool isBeatOn(uint8_t position);
    void cycleBeat(uint8_t position);
    void clear();
    beat_pattern get();
    void setOnBeatChanged(void (*callback)(uint8_t position, uint8_t state));
};

#endif // !H_CARL_BEAT_PATTERN
