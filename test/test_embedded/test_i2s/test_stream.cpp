
#include <Arduino.h>
#include <unity.h>

I2SOutput *output;
WAVFile *file;

void setup() {
  esp_log_level_set("*", ESP_LOG_ERROR);
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS");
    return;
  }
  Serial.println("starting I2S...");
  output = new I2SOutput();
  output->begin();
  Serial.println("I2S started!");

  Serial.println("Loading WAV...");
  file = new WAVFile("/sine.wav", 128);
  Serial.println("WAV loaded!");
  Serial.println("Playing now...");
  output->add(file, 1.0f);
}

void loop() {}
