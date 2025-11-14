#include <Arduino.h>
#include <ESP_I2S.h>
#include <unity.h>

void i2s_test_loop();
void i2s_test_setup();

int runUnityTests(void) {
  UNITY_BEGIN();
  return UNITY_END();
}
void setup() {
  delay(2000);
  i2s_test_setup();

  runUnityTests();
}

void loop() {
  i2s_test_loop();
}

// The GPIO pins are not fixed, most other pins could be used for the I2S function.
// #define I2S_LRC 36 // A4
// #define I2S_BCLK 39 // A3
// #define I2S_DIN 34 // A2
#define I2S_LRC  25 // A1
#define I2S_BCLK 5 // SCK
#define I2S_DIN  26 // A0


const int frequency = 440;    // frequency of square wave in Hz
const int amplitude = 500;    // amplitude of square wave
const int sampleRate = 8000;  // sample rate in Hz

i2s_data_bit_width_t bps = I2S_DATA_BIT_WIDTH_16BIT;
i2s_mode_t mode = I2S_MODE_STD;
i2s_slot_mode_t slot = I2S_SLOT_MODE_STEREO;

const unsigned int halfWavelength = sampleRate / frequency / 2;  // half wavelength of square wave

int32_t sample = amplitude;  // current sample value
unsigned int count = 0;

I2SClass i2s;


void i2s_test_setup() {
  Serial.begin(115200);
  Serial.println("I2S simple tone");

  i2s.setPins(I2S_BCLK, I2S_LRC, I2S_DIN);

  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(mode, sampleRate, bps, slot)) {
    Serial.println("Failed to initialize I2S!");
    while (1);  // do nothing
  }

}

void i2s_test_loop() {
  if (count % halfWavelength == 0) {
    // invert the sample every half wavelength count multiple to generate square wave
    sample = -1 * sample;
  }

  // Left channel, the low 8 bits then high 8 bits
  i2s.write(sample);
  i2s.write(sample >> 8);

  // Right channel, the low 8 bits then high 8 bits
  i2s.write(sample);
  i2s.write(sample >> 8);

  // increment the counter for the next sample
  count++;

}
