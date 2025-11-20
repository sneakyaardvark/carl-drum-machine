#include "CarlI2C.hpp"
#include "CarlI2C_LCDPatterns.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>

static bool serialOut = false;

int[7] buttonPins = [0, 1, 2, 3, 4, 5, 6, 7];

void CarlI2C::wireInit(){
    Wire.begin();
}
    
void CarlI2C::serialInit(){
    Serial.begin(DEFAULT_BAUD);
    serialOut = true;
}

void CarlI2C::GPIOInit(Adafruit_MCP23X17 dev){
    if(!dev.begin_I2C()){
        serialOut ? Serial.println("ERROR: GPIO Expander failed to initalize");
    }

    for(int i=0;i<len(buttonPins);i++){
        dev.pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void CarlI2C::screenInit(){
    lcd.init();
    lcd.backlight();
}
    // init screen

void CarlI2C::addressScan(){
    byte address, error;
    int numDevices;

    serialOut ? Serial.println("scanning for devices");

    for (address = 1; address < 128; address++){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if(!error){
            serialOut ? Serial.println("device found at 0x");
            serialOut ? Serial.println(address, HEX);
            numDevices++;
        }

        elif(error==4){
            serialOut ? Serial.println("unknown device at 0x");
            serialOut ? Serial.println(address, HEX);
        }
    
        if(numDevices==0){
            serialOut ? Serial.println("ERROR: no devices found.");
        }
        else(){
            //check addesses against defaults
        }
    }
}

uint16_t CarlI2C::beatState(uint16_t* reg){
    uint16_t bucket = reg;
    for(int i=0;i<len(buttonPins);i++){
        if(!dev.digitalRead(buttonPins[i])){
            bucket += 2^(2 * i);
            if(serialOut){
                Serial.print("switch ");
                Serial.print(i);
                Serial.println(" pressed");
            }
        }
    }
    reg = bucket;
}
    // updates beat state

void CarlI2C::screenTxt(LiquidCrystal_I2C lcd, String message){
    lcd.setCursor(0,0);
    lcd.print(karatL);
    lcd.print(message);
    lcd.print(karatR);
    if(serialOut){
        Serial.print("printed <");
        Serial.print(message);
        Serial.println("> to LCD");
    }
}
    // update text fields

void CarlI2C::screenGfx(LiquidCrystal_I2C lcd){}
    // screen effects

