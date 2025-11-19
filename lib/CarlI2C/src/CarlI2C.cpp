#include "CarlI2C.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystalI2C.h>

static bool serialOut = false;

void wireInit(){
    Wire.begin();
}
    
void serialInit(){
    Serial.begin(DEFAULT_BAUD);
    serialOut = true;
}

void screenInit(){

}
    // init screen

void addressScan(){
    byte address, error;
    byte[] devices
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
    
        if(numDevices==0){}
        else(){}
    }


}
    // scans/checks addresses of devices

void IOState(){

}
    // reads GPIO state

void screenTxt(){}
    // update text fields

void screenGfx(){}
    // screen effects