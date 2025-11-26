#include <stdlib.h>

void writeConfigLED(uint8_t state){}

void writeBeatLED(Adafruit_TLC5947 tlc, uint16_t state){
    uint16_t dummy, mask, wb;
    for(int i=0; i<16; i++){
        mask = 2^i;
        if(state & mask){
            tlc.setPWM(i, PWM_ON);
            wb += mask;
        }else{
            tlc.setPWM(i, PWM_OFF);
        }
    }
    state = wb;
}

/*mask = 2^i;
        dummy = state & mask;
        
        (dummy > 0)
            ? dummy = state - mask
            : dummy = state + mask;
        */