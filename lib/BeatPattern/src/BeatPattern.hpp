/**
 * @file BeatPattern.hpp
 * @brief An object for manipulating the beat patterns
 */
#ifndef H_CARL_BEAT_PATTERN
#define H_CARL_BEAT_PATTERN
#include <stdint.h>

/**
 * @brief the beat pattern type
 */
typedef uint16_t beat_pattern;

class BeatPattern {
  private:
    beat_pattern beat;

  public:
    BeatPattern();
    /**
     * @brief cycle a beat
     * @param position the beat to cycle
     */
    void cycleBeat(uint8_t position);
    /**
     * @brief reset this pattern (set all to 0)
     */
    void clear(void);
    /**
     * @brief get the underlying beat pattern
     * Note! Use cycleBeat() for changing, this returns a value, not a reference!
     * @return the pattern
     */
    beat_pattern get(void);
};

#endif // !H_CARL_BEAT_PATTERN
