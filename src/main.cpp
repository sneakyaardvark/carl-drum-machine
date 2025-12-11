#include "config.h"
#include "CarlI2C.hpp"
#include "CarlSerial.hpp"
#include <Arduino.h>
//#include <BeatPattern.hpp>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>
#include <Adafruit_TLC5947.h>

#define light 4095
#define numDevices 1
#define wait 5000

Adafruit_MCP23X17 dev;

Adafruit_TLC5947 tlc = Adafruit_TLC5947(numDevices, SPI_CL, SPI_LAT, SPI_DATA);

struct I2CDevice* devices;

uint8_t res = 11;
uint8_t enab = 9;

uint8_t d0 = 0;
uint8_t d1 = 1;
uint8_t d2 = 2;
uint8_t d3 = 3;
uint8_t d4 = 4;
uint8_t d5 = 5;
uint8_t d6 = 6;
uint8_t d7 = 7;

LiquidCrystal lcd(res, enab, d0, d1, d2, d3, d4, d5, d6, d7);

void setup() {
    Wire.begin();
    Serial.begin(115200);

    // gpio
    if (!dev.begin_I2C()) {
        Serial.println("Error.");
        while (1);
    }

    dev.pinMode(0, INPUT);

    // LCD
    lcd.begin(16,4);

    // LED
    tlc.begin();
}

void loop() {
    // LED test
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


    // GPIO test
    int iterator = 8;
    for(int i=0;i<iterator;i++){
        if(!dev.digitalRead(i)){
                
            // interlock 

            Serial.print("switch ");
            Serial.print(i);
            Serial.println(" pressed");
            
        }
    }
    
    // LCD test
    int col, row = 0;
    String message = "Hello world!";
    lcd.setCursor(col, row);
    lcd.print(message);

    Serial.print("printed <");
    Serial.print(message);
    Serial.println("> to LCD");

}

