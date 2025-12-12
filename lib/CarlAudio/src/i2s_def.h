/**
 * @file i2s_def.h
 * @brief Misc I2S definitions
 */
#ifndef H_I2S_DEF
#define H_I2S_DEF

#include <stdint.h>

#define I2S_DOUT 26 // A0
#define I2S_BCLK 5 // SCK
#define I2S_LRCLK 25 // A1
/**
 * @brief the sample rate of the I2S bus
 */
#define I2S_SAMPLE_RATE 48000
/**
 * @brief the type used to store the LPCM samples
 */
typedef int16_t i2s_sample_t;
/**
 * @brief the maximum possible value held by i2s_sample_t
 */
#define I2S_SAMPLE_MAX INT16_MAX

#endif // !H_I2S_DEF
