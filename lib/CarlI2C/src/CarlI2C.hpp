#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>

// prelim: check i2c address
class CarlI2C {
    private:

    public:
        void wireInit();
        // Wire.begin()

        void GPIOInit();

        void screenInit();
        // lcd.init()
        // variables that are needed quickly
        //      probably good at top 


        void addressScan();

        uint16_t beatState();
        //ll
        // uses a pointer to avoid changing that data directly
        //      have some control signal array var local to main or smth
        // init i2c wire vars
        // data read call
        //      quick valid check
        //      map to virtual space

        
        void screenTxt();
        // only called when text fields update
        //      in this case only the name of the voice

        void screenGfx();
        // screen effects for patch selection, blinking indicator

}
// input parser from gpio module

// output to screen

// output to LEDs


#endif // !H_CARL_I2C
