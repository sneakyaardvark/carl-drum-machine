#include "config.h"
#include "CarlI2C.hpp"
#include "CarlSerial.hpp"
#include <Arduino.h>
//#include <BeatPattern.hpp>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>
#include <Adafruit_TLC5947.h>

struct carl {
  uint8_t current_voice = 0;
  //beat_pattern pattern_mtx[NUM_VOICES][NUM_PATTERNS];
  uint8_t tempo = 120; 
};

struct carl CARL;

struct I2CDevice* devices;

LiquidCrystal* lcd();

Adafruit_MCP23X17 dev;

#define light 4095
#define numDevices 1
#define wait 5000

Adafruit_TLC5947* tlc;
tlc = Adafruit_TLC5947(numDevices, SPI_CL, SPI_LAT, SPI_DATA);

void setup() {
    //CarlI2C::wireStart();
    Wire.begin();
    //CarlI2C::serialOut(true);
    Serial.begin(115200);

    //CarlI2C::GPIOInit(dev);
    //CarlI2C::screenInit(lcd);
    CarlSerial::serialInit(tlc, "TLC5947 init sequence");

    CarlI2C::addressScan(devices);
}

void loop() {
/*  // LED test
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
*/

    // GPIO test
    //CarlI2C::inputParse();

    // LCD test
    CarlI2C::arbitraryPrint(&lcd, 0, 0, "Hello, World!");
  
}

