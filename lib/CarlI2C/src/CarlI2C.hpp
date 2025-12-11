//#include "CarlI2C_LCDPatterns.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>

enum I2CTag {GPIO, LCD, UNK} ;

struct I2CDevice {
    String name;
    int index;
    byte address;
    bool busMember;
};

// prelim: check i2c address
class CarlI2C {
    private:
        //void I2CDeviceBuild(I2CDevice devices[4], int idx, byte addr, bool busM);

    public:
        void wireStart();
        // Wire.begin()

        void serialOut(bool caset);
        // lcd.init()
        // variables that are needed quickly
        //      probably good at top 

        void GPIOInit(Adafruit_MCP23X17 &dev);

        void screenInit(LiquidCrystal &lcd);

        void addressScan(I2CDevice devices[4]);

        void inputParse(Adafruit_MCP23X17 &dev);

        uint16_t beatState(Adafruit_MCP23X17 &dev, uint16_t* reg);
        //ll
        // uses a pointer to avoid changing that data directly
        //      have some control signal array var local to main or smth
        // init i2c wire vars
        // data read call
        //      quick valid check
        //      map to virtual space

        void GPIOInterrupt(Adafruit_MCP23X17 &dev);

        void voiceText(LiquidCrystal &lcd, String message);
        // only called when text fields update
        //      in this case only the name of the voice

        void arbitraryPrint(LiquidCrystal &lcd, int col, int row, String message);
        // screen effects for patch selection, blinking indicator

        void screenGfx(LiquidCrystal &lcd, int token);
        
};
// input parser from gpio module

// output to screen

// output to LEDs
