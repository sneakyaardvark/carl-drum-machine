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
#include <list>
#include <stdint.h>
#include "WAVFile.hpp"

/**
 * @brief a representation of a sample, such as a drum kick.
 * @see I2SOutput::add()
 */
typedef struct voice_t {
  WAVFile *src; /**< the WAV file corresponding to this sample */
  volatile uint32_t play_position; /**< the play position of this sample */
  float volume; /**< the volume of this sample */
} Voice_t;

/**
 * @brief An I2S output.
 */
class I2SOutput {
  private:
    TaskHandle_t i2sWriterTask;
    std::list<Voice_t> voices;
    I2SClass I2S;
  public:
    /** 
     * @brief Initialize the I2S output for operation
     */
    void begin();
    /**
     * @brief Add a file to send out over I2S
     * @param file the WAV to add
     * @param volume the volume of the file
     */
    void add(WAVFile *file, float volume);

    friend void I2SWriterTask(void* param);
};

#endif // !H_I2SOUTPUT
