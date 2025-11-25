/**
 * @file playback.hpp
 * @brief playback for CARL
 */
#ifndef H_CARL_PLAYBACK
#define H_CARL_PLAYBACK
#include <I2SOutput.hpp>
#include <stdint.h>
#include <BeatPattern.hpp>

typedef struct s_carl {
  uint8_t current_voice;
  float tempo;
  BeatPattern patterns[4];
} CARL;

class CarlPlayback {
  public:
    I2SOutput i2s;
    CarlPlayback(float tempo, uint8_t num_tracks, void (*callback)(uint32_t step, uint8_t track));
    // CarlPlayback(float tempo, uint8_t num_tracks);
    CARL *carl;
    void setTempo(float tempo);
    void playVoice(uint8_t voice);
    void play(void);
    void stop(void);

    friend void onStepCallback(uint32_t tick, uint8_t track);
};

#endif // !H_CARL_PLAYBACK
