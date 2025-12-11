#include <stdlib.h>
//#include "config.h"
#include <Arduino.h>
#include <Adafruit_TLC5947.h>

void writeConfigLED(Adafruit_TLC5947 &tlc, uint8_t state){}

void writeBeatLED(Adafruit_TLC5947 &tlc, uint16_t state){
    uint16_t dummy, mask, wb;
    for(int i=0; i<16; i++){
        mask = 2^i;
        if(state & mask){
            tlc.setPWM(i, 4000);
            wb += mask;
        }else{
            tlc.setPWM(i, 0);
        }
    }
    state = wb;
}

void serialInit(Adafruit_TLC5947 &tlc, String message){
    Serial.println(message);

    bool state = tlc.begin();
    uint16_t tester = tlc.getPWM(0);
    Serial.print("TLC=");
    Serial.println(state);
    Serial.print("getPWM=");
    Serial.println(tester);

    if(!state){
        Serial.println("ERROR: TLC5947 initialization failed.");
    } else {
        Serial.println("TLC init successful.");
    }
}
/*mask = 2^i;
        dummy = state & mask;
        
        (dummy > 0)
            ? dummy = state - mask
            : dummy = state + mask;
        */