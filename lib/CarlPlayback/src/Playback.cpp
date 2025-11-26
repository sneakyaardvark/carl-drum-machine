#include "Playback.hpp"
#include <uClock.h>
#include <esp_log.h>

static const char *TAG = "PLAYBACK";

CarlPlayback::CarlPlayback(float tempo, uint8_t num_tracks, void (*callback)(uint32_t step, uint8_t track)) {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  i2s.enabled = false;
  i2s.begin();
  uClock.init();
  uClock.setOutputPPQN(uClock.PPQN_96);
  uClock.setOnStep(callback, num_tracks);

  uClock.setTempo(tempo);
}

void CarlPlayback::setTempo(float tempo) {
  uClock.setTempo(tempo);
}

void CarlPlayback::playVoice(uint8_t voice) {
  i2s.play(voice);
}

void CarlPlayback::play() {
  i2s.enabled = true;
  uClock.start();
}

void CarlPlayback::stop() {
  i2s.enabled = false;
  uClock.stop();
}
