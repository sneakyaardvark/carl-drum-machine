#include <stdlib.h>
#include <Arduino.h>
#include <Adafruit_TLC5947.h>
class CarlSerial {
    private:

    public:
        //void wireStart();
        void writeConfigLED(Adafruit_TLC5947 &tlc, uint8_t state);
        void writeBeatLED(Adafruit_TLC5947 &tlc, uint16_t state);
        void serialInit(Adafruit_TLC5947 &tlc, String message);
};