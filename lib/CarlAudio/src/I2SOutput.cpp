/** 
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids/blob/main/src/Audio/I2SOutput.cpp
 * Under the Unlicense
 */
#include "I2SOutput.hpp"
#include "freertos/idf_additions.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_FRAMES_TO_SEND 64

typedef struct i2s_frame {
  int16_t left;
  int16_t right;
} frame_t;

void I2SWriterTask(void* param) {
  I2SOutput* output = (I2SOutput*)param;
  volatile int availableBytes = 0;
  volatile int buffer_position = 0;
  frame_t* frames = (frame_t*)malloc(sizeof(frame_t) * NUM_FRAMES_TO_SEND);
  while (true)
  {
    if (1 /* TODO: check if we should be playing back */) {
      size_t bytesWritten = 0;
      do {
        // buffer has been sent -- create a new one
        if (availableBytes == 0) {
          for (int i = 0; i < NUM_FRAMES_TO_SEND; i++) {
            float sample = 0;
            for (auto &voice : output->voices) {
              if (voice.play_position < voice.src->get_number_samples()) {
                sample += voice.volume * (voice.src->get_sample(voice.play_position) - 128.0f) / 128.0f;
                voice.play_position += 1;
              }
            }
            // apply clipping
            sample = tanhf(sample);
            // output it
            frames[i].left = sample * 16383; // multiply to get a reasonable sample value out of the ratio
            frames[i].right = sample * 16383;
          }
          // how many bytes do we now have to send
          availableBytes = NUM_FRAMES_TO_SEND * sizeof(frame_t);
          // reset the buffer
          buffer_position = 0;

        }
        // do we have something to write?
        if (availableBytes > 0) {
          // write to I2S
          bytesWritten = output->I2S.write((uint8_t*)frames, availableBytes);
          availableBytes -= bytesWritten;
          buffer_position += bytesWritten;

        }
      } while (bytesWritten > 0);
    }
  }
}

void I2SOutput::begin() {
  I2S.setPins(I2S_BCLK, I2S_LRCLK, I2S_DOUT);
  I2S.begin(I2S_MODE_STD, 48000, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO);
  
  xTaskCreatePinnedToCore(I2SWriterTask, "i2s_writer", 4096, this, 2, &i2sWriterTask, 1);
}

void I2SOutput::add(WAVFile* file, float volume) {
  for (auto &voice : voices) {
    if (voice.play_position == voice.src->get_number_samples())
    {
        voice.src = file;
        voice.play_position = 0;
        voice.volume = volume;
        return;
    }
  }
  voices.push_back({.src = file,
                    .play_position = 0,
                    .volume = volume});
}
