#include "config.h"
#include <Arduino.h>
#include <BeatPattern.hpp>

struct carl {
  uint8_t current_voice = 0;
  beat_pattern pattern_mtx[NUM_VOICES][NUM_PATTERNS];
  uint8_t tempo = DEFAULT_TEMPO; 
};

struct carl CARL;

void setup() {
//test modes:
//	0 - bare GPIO hardware testing - switches, pots
//		  connected directly to device
//	1 - signal component testing - LED, LCD, (SD) 
//		  devices all connected, testing modularly or in sequence
//	2 - audio signal component testing
//		  speaker/speaker amp testing with signal sweep, pwm variation signal

}

void loop() {
//test mode select
//
//  0
//    user-defined pins through user input OR file
//    CLI output for concurrent
//      can swap components at will, device wont care
//  1
//    all these pins should be fairly standardized over our workflow
//    concurrent or sequential display operation
//  2
//    all these pins are also standardized over our workflow
//    signal sweep, pwm output
}

