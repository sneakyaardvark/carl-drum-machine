/** 
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids/blob/main/src/Audio/I2SOutput.cpp
 * Under the Unlicense
 */
#include "I2SOutput.hpp"
#include "esp_log.h"
#include "esp_log_level.h"
#include "freertos/idf_additions.h"
#include <esp_log.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_FRAMES_TO_SEND 64

static const char *TAG = "I2S";

typedef struct i2s_frame {
  i2s_sample_t left;
  i2s_sample_t right;
} frame_t;

void I2SWriterTask(void* param) {
  I2SOutput* output = (I2SOutput*)param;
  volatile int availableBytes = 0;
  volatile int buffer_position = 0;
  frame_t* frames = (frame_t*)malloc(sizeof(frame_t) * NUM_FRAMES_TO_SEND);
  if (frames == NULL) {
    ESP_LOGE(TAG, "unable to allocate frames ptr");
  }
  while (true)
  {
    if (output->enabled) {
      size_t bytesWritten = 0;
      do {
        // buffer has been sent -- create a new one
        if (availableBytes == 0) {
          for (int i = 0; i < NUM_FRAMES_TO_SEND; i++) {
            float sample = 0;
            for (auto &voice : output->voices) {
              if (xSemaphoreTake(voice.xMutex, portMAX_DELAY) == pdTRUE) {
                ESP_LOGD(TAG, "play=%u;pp=%u;ttl_s=%u", voice.play, voice.play_position, voice.src->get_total_number_samples());
                if (voice.play && voice.play_position < voice.src->get_total_number_samples()) {
                  sample += (float)(voice.src->get_sample(voice.play_position)) / I2S_SAMPLE_MAX;
                  ESP_LOGD(TAG, "add=%u", voice.src->get_sample(voice.play_position));
                  voice.play_position += 1;
                } else {
                  ESP_LOGD(TAG, "voice finished playing");
                }
                xSemaphoreGive(voice.xMutex);
              }
              
            }
            // apply clipping
            sample = tanhf(sample);
            ESP_LOGD(TAG, "sample=%f", sample * I2S_SAMPLE_MAX);

            // output it
            frames[i].left = frames[i].right = sample * I2S_SAMPLE_MAX;
          }
          // how many bytes do we now have to send
          availableBytes = NUM_FRAMES_TO_SEND * sizeof(frame_t);
          // reset the buffer
          buffer_position = 0;

        }
        // do we have something to write?
        if (availableBytes > 0) {
          // write to I2S. If for some reason not all of the bytes get written, we save
          // the buffer position and offset the address of the frames
          bytesWritten = output->I2S.write(buffer_position + (uint8_t*)frames, availableBytes);
          availableBytes -= bytesWritten;
          buffer_position += bytesWritten;
          ESP_LOGD(TAG, "sent %u bytes", bytesWritten);
        }
      } while (bytesWritten > 0);
    } else {
      // if (availableBytes != 0) {
      //   availableBytes = 0;
      // }
      vTaskDelay(1);
    }
  }
}

void I2SOutput::begin() {
  esp_log_level_set(TAG, ESP_LOG_ERROR);
  I2S.setPins(I2S_BCLK, I2S_LRCLK, I2S_DOUT);
  I2S.begin(I2S_MODE_STD, I2S_SAMPLE_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO);
  
  xTaskCreatePinnedToCore(I2SWriterTask, "i2s_writer", 4096, this, 2, &i2sWriterTask, 1);
}

void I2SOutput::setVoice(uint8_t num, WAVFile *file) {
  ESP_LOGE(TAG, "Setting voice %u", num);
  Voice_t v = {
    .src = file,
    .play = false,
    .xMutex = xSemaphoreCreateMutex(),
    .play_position = 0,
  };
  voices[num] = v;
}

void I2SOutput::play(uint8_t voice) {
  if(xSemaphoreTake(voices[voice].xMutex, portMAX_DELAY) == pdTRUE) {
    voices[voice].src->reset();
    voices[voice].play_position = 0;
    voices[voice].play = true;
    xSemaphoreGive(voices[voice].xMutex);
  }
  ESP_LOGE(TAG, "voice %u play = %d", voice, voices[voice].play);
}
