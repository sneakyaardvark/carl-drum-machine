#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>

// prelim: check i2c address
class CarlI2C {
    private:

    public:
        void wireStart();
        // Wire.begin()

        void serialOut();
        // lcd.init()
        // variables that are needed quickly
        //      probably good at top 

        void GPIOInit();

        void screenInit(LiquidCrystal_I2C lcd);

        void addressScan();

        uint16_t beatState(Adafruit_MCP23X17 dev, uint16_t* reg);
        //ll
        // uses a pointer to avoid changing that data directly
        //      have some control signal array var local to main or smth
        // init i2c wire vars
        // data read call
        //      quick valid check
        //      map to virtual space

        void GPIOInterrupt(Adafruit_MCP23X17 dev);

        void voiceText(LiquidCrystal_I2C lcd, String message);
        // only called when text fields update
        //      in this case only the name of the voice

        void ArbitraryPrint(LiquidCrystal_I2C lcd, int col, int row, String message);
        // screen effects for patch selection, blinking indicator

        void screenGfx(LiquidCrystal_I2C lcd);
}
// input parser from gpio module

// output to screen

// output to LEDs


#endif // !H_CARL_I2C
