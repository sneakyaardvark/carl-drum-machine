#include "CarlI2C.hpp"
//#include "CarlI2C_LCDPatterns.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystal.h>  
#include <Adafruit_MCP23X17.h>

static bool serialOut = false;

// device id index struct

// pins for button inputs - values are GPIO pins 
int buttonPins[] = {0, 1, 2, 3, 4, 5, 6};

int GPIO_ADDR = 0x14;
int LCD_ADDR = 0x11;
// initializes i2c wire variable
void CarlI2C::wireStart(){
    Wire.begin();
}

/* enables or disables serial output communications
void CarlI2C::serialOut(bool case){
    serialOut = case;
    serialOut = (true) ? Serial.begin(DEFAULT_BAUD) : Serial.end();
}
*/

// initialization for GPIO module
void CarlI2C::GPIOInit(Adafruit_MCP23X17 &dev){
    if(!dev.begin_I2C()){ //nonstarter error checking
        Serial.println("ERROR: GPIO Expander failed to initalize");
    }

    int iterator = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for(int i=0;i<iterator;i++){ //enable input button pins with internal pullup
        dev.pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

/* initialization for LCD screen
void CarlI2C::screenInit(LiquidCrystal &lcd){
    lcd.init();
    lcd.backlight();
}
*/

/* builder command for I2CDevice array
void CarlI2C::I2CDeviceBuild(I2CDevice devices[4],  int idx, byte addr, bool busM){
    devices->name = "generic";
    devices->index = idx;
    devices->address = addr;
    devices->busMember = busM;
}
*/

// scans I2C bus for devices, catalogues them
void CarlI2C::addressScan(I2CDevice devices[4]){
    byte address, error;
    int numDevices;

    //serial communications
    Serial.println("scanning for devices");

    for (address = 1; address < 128; address++){
        String deviceName;
        bool busMember;

        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        Serial.print("address=");
        Serial.println(address);
        switch(error){
            case 0: // add recognized devices to device id index
                if(address == GPIO_ADDR){
                    deviceName = "GPIO";
                }
                else if(address == LCD_ADDR){
                    deviceName = "LCD";
                }
                else{
                    deviceName = "ARB";
                }
        
                busMember = true; 

                print("mappable device found at ");
                println(address);
                print("name ");
                println(deviceName);
                //I2CDeviceBuild(devices, deviceName, numDevices, address, busMember);
                break;
            
            case 4:
                deviceName = "UNK";
                busMember = false;

                print("UNK device found at ");
                println(address);
                //I2CDeviceBuild(devices, deviceName, numDevices, address, busMember);
                break;

            default:
                Serial.print("ERROR: unknown I2C Bus error [");
                Serial.print(error);
                Serial.println("]");
                break;

        
        }
        numDevices++;
    }
    if(numDevices = 0){
        Serial.println("ERROR: No I2C devices registered.");
    }

    Serial.print("numDevices=");
    Serial.println(numDevices);
}


void CarlI2C::inputParse(Adafruit_MCP23X17 &dev){
    int iterator = sizeof(buttonPins) / sizeof(buttonPins[0]);
    for(int i=0;i<iterator;i++){
        if(!dev.digitalRead(buttonPins[i])){
            
            // interlock 

            Serial.print("switch ");
            Serial.print(i);
            Serial.println(" pressed");
            
        }
    }
}

/* updates 16bit number representing beat state based on check loop 
uint16_t CarlI2C::beatState(uint16_t* reg){
    uint16_t bucket = reg;
    for(int i=0;i<len(buttonPins);i++){
        if(!dev.digitalRead(buttonPins[i])){
            bucket += 2^(2 * i);

            Serial.print("switch ");
            Serial.print(i);
            Serial.println(" pressed");
            
        }
    }

    reg = bucket;
    //return bucket;
}
*/

// beatState driven by value representing switch pressed
// todo <future predicting>
//uint16_t CarlI2C::beatDrive(Adafruit_MCP23X17 dev, uint16_t* reg, [uint8_t/int] switch){}

//handler for GPIO interrupt routine
//todo
void CarlI2C::GPIOInterrupt(Adafruit_MCP23X17 &dev){}

// updates voice text of LCD (top text line)
void CarlI2C::voiceText(LiquidCrystal &lcd, String message){
    lcd.setCursor(0,0);
    lcd.print('[');
    lcd.print(message);
    lcd.print(']');

    Serial.print("printed [");
    Serial.print(message);
    Serial.println("] to LCD");

}

// arbitrary text update for screen          
void CarlI2C::arbitraryPrint(LiquidCrystal &lcd, int col, int row, String message){
    lcd.setCursor(col, row);
    lcd.print(message);

    Serial.print("printed <");
    Serial.print(message);
    Serial.println("> to LCD");

}

// draw/update screen graphical effects
// todo
void CarlI2C::screenGfx(LiquidCrystal &lcd, int token){}

