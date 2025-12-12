#include "config.h"
#include <Arduino.h>
#include <Playback.hpp>
#include <WAVFile.hpp>
#include <esp_log.h>
#include <uClock.h>
#include <SPIFFS.h>

CARL carl = {
    .tempo = DEFAULT_TEMPO,
};
CarlPlayback *pb;
WAVFile *file;

unsigned long last_millis;
volatile uint32_t test = 0;

void onStepCallback(uint32_t tick, uint8_t track) {
  if (tick % 2) {
    // 1/8
    if (track == 0) {
      // pb->playVoice(0);
      // ESP_LOGE("stepCB", "[%u] tick", track);
    }
  }
}
void setup() {
  esp_log_level_set("*", ESP_LOG_ERROR);
  if (!SPIFFS.begin(true)) {
    ESP_LOGE("main", "Error mounting SPIFFS");
    return;
  }

  file = new WAVFile("/sine.wav", 128);
  pb = new CarlPlayback(DEFAULT_TEMPO, NUM_VOICES, onStepCallback);
  pb->carl = &carl;
  pb->i2s.setVoice(0, file);
  pb->i2s.setVoice(1, file);
  pb->i2s.setVoice(2, file);
  pb->i2s.setVoice(3, file);
  pb->play();
  pb->playVoice(0);
}

void loop() {
  unsigned long now = millis();
  if (now - last_millis > 3000) {
    ESP_LOGE("main", "play3");
    pb->playVoice(0);
    last_millis = now;
  }
  // Your main code here
  // if (test == 96) {
  //   ESP_LOGE("PLAYBACK", "beat!");
  //   test = 0;
  // }
}
