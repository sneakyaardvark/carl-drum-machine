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

//operating modes
//	0 - primary operating mode (BEAT MACHINE)
//		  boot process > looping sound playback logic
//	1 - debug mode - troubleshooting
//		  side-loaded boot > looping helloworld/component diagnostics
*/

#define num_devices 1
#define data 17
#define clock 4
#define latch 21

#define PWM 2048

#define channels 17
#define light 100

#define wait 200

Adafruit_TLC5947 tlc = Adafruit_TLC5947(num_devices, clock, latch, data);

void setup() {
  Serial.begin(DEFAULT_BAUD);

  Serial.println("LED Array test");

  if(!tlc.begin()){
    Serial.println("ERROR: TLC5947 initialization failed.");
  }
}

void loop() {
  tlc.setLED(0, light, light, light);
  tlc.write();
  delay(5000);
  tlc.setLED(0, 0,0,0);
  tlc.write();
  delay(5000);
}
void writeConfigLED(uint8_t state){}
void writeBeatLED(uint16_t state){}
  /*
  for(int i=0;i<=channels;i++){
    if(i>0){
      tlc.setLED((i-1), 0, 0, 0);
      tlc.write();
      delay(wait);
    }else{
      tlc.setLED(17, 0, 0, 0);
      tlc.write();
      delay(wait);
    }
    tlc.setLED(i, light, light, light);
    tlc.write();
    delay(wait);
  */
  

