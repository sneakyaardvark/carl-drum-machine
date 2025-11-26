/*
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids/blob/main/src/Audio/I2SOutput.h
 * Under the Unlicense
 */
/**
 * @file I2SOutput.hpp
 * @brief A wrapper for outputting on I2S using ESP_I2S
 *
 * On begin(), I2SOutput initializes I2S through the ESP_I2S API, and begins a writer task in a new thread.
 * This allows the I2S output to be non-blocking, and to layer voices (each WAV) added by add() for polyphony.
 */
#ifndef H_I2SOUTPUT
#define H_I2SOUTPUT

#include <ESP_I2S.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <stdint.h>
#include "WAVFile.hpp"

/**
 * @brief a representation of a sample, such as a drum kick.
 * @see I2SOutput::add()
 */
typedef struct voice_t {
  WAVFile *src; /**< the WAV file corresponding to this sample */
  volatile bool play;
  SemaphoreHandle_t xMutex;
  volatile uint32_t play_position; /**< the play position of this sample */
} Voice_t;

/**
 * @brief An I2S output.
 */
class I2SOutput {
  private:
    TaskHandle_t i2sWriterTask;
    Voice_t voices[4];
    I2SClass I2S;
  public:
    volatile bool enabled;
    /** 
     * @brief Initialize the I2S output for operation
     */
    void begin();
    void play(uint8_t voice);
    void setVoice(uint8_t num, WAVFile *file);

    friend void I2SWriterTask(void* param);
};

#endif // !H_I2SOUTPUT
