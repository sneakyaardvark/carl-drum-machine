#include "CarlI2C.hpp"
#include "CarlI2C_LCDPatterns.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystalI2C.h>

static bool serialOut = false;

void CarlI2C::wireInit(){
    Wire.begin();
}
    
void CarlI2C::serialInit(){
    Serial.begin(DEFAULT_BAUD);
    serialOut = true;
}

void CarlI2C::screenInit(){

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

void CarlI2C::IOState(){
}
    // reads GPIO state

void CarlI2C::screenTxt(){}
    // update text fields

void CarlI2C::screenGfx(){}
    // screen effects