#ifndef H_CARL_HARDWARE_TEST
#define H_CARL_HARDWARE_TEST
#include <stdint.h>

class modeDebug {
  //private:
  public:
    void Switches();
    void Potentiometers();

    void LCD();
    void LEDController();

    void AudioOut();

    void Power();
};
#endif // !H_CARL_BEAT_PATTERN
