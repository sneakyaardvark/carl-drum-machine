#include "config.h"
#include <Arduino.h>
//#include <BeatPattern.hpp>
#include <Adafruit_TLC5947.h>

/*
struct carl {
  uint8_t current_voice = 0;
  beat_pattern pattern_mtx[NUM_VOICES][NUM_PATTERNS];
  uint8_t tempo = DEFAULT_TEMPO; 
};

struct carl CARL;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

Adafruit_MCP23X17 dev;
*/

#define light 4095
#define numDevices 1
#define wait 5000

Adafruit_TLC5947 tlc = Adafruit_TLC5947(numDevices, SPI_CL, SPI_LAT, SPI_DATA);

void setup() {
  Serial.begin(DEFAULT_BAUD);

  Serial.println("LED Array test");

  bool state = tlc.begin();
  uint16_t tester = tlc.getPWM(0);
  Serial.println(state);
  Serial.println(tester);
  if(!state){
    Serial.println("ERROR: TLC5947 initialization failed.");
  } else {
    Serial.println("TLC init suceeded, goto loop.");
  }
}

void loop() {
  uint16_t tester;
  Serial.println("top");
  tlc.setPWM(0, light);
  tlc.write();
  tester = tlc.getPWM(0);
  Serial.println(tester);
  delay(wait);
  Serial.println("blink");
  tlc.setPWM(0, 0);
  tlc.write();
  tester = tlc.getPWM(0);
  Serial.println(tester);
  delay(wait);
}

