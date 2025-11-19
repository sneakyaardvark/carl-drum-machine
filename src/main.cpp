#include "config.h"
#include <Arduino.h>
#include <BeatPattern.hpp>
#include <WAVFile.hpp>
#include <SPIFFS.h>
#include <I2SOutput.hpp>

struct carl {
  uint8_t current_voice = 0;
  beat_pattern pattern_mtx[NUM_VOICES][NUM_PATTERNS];
  uint8_t tempo = DEFAULT_TEMPO; 
};

struct carl CARL;

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS");
    return;
  }
  Serial.println("starting I2S...");
  I2SOutput *output = new I2SOutput();
  output->begin();
  Serial.println("I2S started!");

  Serial.println("Loading WAV...");
  WAVFile *file = new WAVFile("/sine.wav", 128);
  Serial.println("WAV loaded!");
  Serial.println("Playing in 2.0 seconds...");
  delay(2);
  output->add(file, 1.0f);
}

void loop() {}
