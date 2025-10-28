#ifndef H_CARL_BEAT_PATTERN
#define H_CARL_BEAT_PATTERN
#include <stdint.h>

typedef uint32_t beat_pattern;

beat_pattern cycleBeat(beat_pattern beat, uint8_t position);

#endif // !H_CARL_BEAT_PATTERN
