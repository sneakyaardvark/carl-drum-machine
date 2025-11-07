#include <Arduino.h>
#include <WAVFile.hpp>
#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS");
    return;
  }

  WAVFile* file = new WAVFile("/sine.wav", 64);
}

void loop() {

}

