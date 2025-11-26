#include "CarlI2C.hpp"
#include "CarlI2C_LCDPatterns.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>

static bool serialOut = false;

// device id index struct
struct I2CDevice {
    String name;
    int index;
    byte address;
    bool busMember;
}

// pins for button inputs - values are GPIO pins 
int[7] buttonPins = [0, 1, 2, 3, 4, 5, 6, 7];

// initializes i2c wire variable
void CarlI2C::wireStart(){
    Wire.begin();
}

// enables or disables serial output communications
void CarlI2C::serialOut(bool case){
    serialOut = case;
    serialOut = (true) ? Serial.begin(DEFAULT_BAUD) : Serial.end();
}

// initialization for GPIO module
void CarlI2C::GPIOInit(Adafruit_MCP23X17 dev){
    if(!dev.begin_I2C()){ //nonstarter error checking
        serialOut = (true) ? Serial.println("ERROR: GPIO Expander failed to initalize");
    }

    for(int i=0;i<len(buttonPins);i++){ //enable input button pins with internal pullup
        dev.pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

// initialization for LCD screen
void CarlI2C::screenInit(LiquidCrystal_I2C lcd){
    lcd.init();
    lcd.backlight();
}

// builder command for I2CDevice array
void CarlI2C::I2CDeviceBuild(I2CDevice[MAX_DEVICES] devices, String tag, int idx, byte addr, bool busM){
    devices.name = tag;
    devices.index = idx;
    devices.address = addr;
    devices.busMember = busM;
}

// scans I2C bus for devices, catalogues them
void CarlI2C::addressScan(I2CDevice[MAX_DEVICES]* devices){
    byte address, error;
    int numDevices;

    //serial communications
    serialOut = (true) ? Serial.println("scanning for devices");

    for (address = 1; address < 128; address++){
        String deviceName;
        bool busMember;

        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        switch(error){
            case 0: // add recognized devices to device id index
                address = (GPIO_ADDR) ? deviceName = "GPIO";
                address = (LCD_ADDR) ? deviceName = "LCD";
                deviceName = "ARB";
                busMember = true; 

                I2cDeviceBuild(devices, deviceName, numDevices, address, busMember);
                break;
            
            case 4:
                deviceName = "UNK";
                busMember = false;

                I2cDeviceBuild(devices, deviceName, numDevices, address, busMember);
                break;

            default:
                serialOut = (true) ? Serial.print("ERROR: unknown I2C Bus error [");
                serialOut = (true) ? Serial.print(error);
                serialOut = (true) ? Serial.println("]");
                break;

        
        }
        numDevices++;
    }
    if(numDevices = 0){
        serialOut = (true) ? Serial.println("ERROR: No I2C devices registered.");
    }
}

// updates 16bit number representing beat state based on check loop 
uint16_t CarlI2C::beatState(Adafruit_MCP23X17 dev, uint16_t* reg){
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
    //return bucket;
}

// beatState driven by value representing switch pressed
// todo <future predicting>
//uint16_t CarlI2C::beatDrive(Adafruit_MCP23X17 dev, uint16_t* reg, [uint8_t/int] switch){}

//handler for GPIO interrupt routine
//todo
void CarlI2C::GPIOInterrupt(Adafruit_MCP23X17 dev){}

// updates voice text of LCD (top text line)
void CarlI2C::voiceText(LiquidCrystal_I2C lcd, String message){
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

// arbitrary text update for screen          
void CarlI2C::arbitraryPrint(LiquidCrystal_I2C lcd, int col, int row, String message){
    lcd.setCursor(col, row);
    lcd.print(message);
    if(serialOut){
        Serial.print("printed <");
        Serial.print(message);
        Serial.println("> to LCD");
    }
}

// draw/update screen graphical effects
// todo
void CarlI2C::screenGfx(LiquidCrystal_I2C lcd, charLCD token){}

