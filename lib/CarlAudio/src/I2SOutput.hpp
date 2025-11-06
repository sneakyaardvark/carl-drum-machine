#ifndef H_I2SOUTPUT
#define H_I2SOUTPUT

#include <ESP_I2S.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <list>
#include <stdint.h>
#include "WAVFile.hpp"

#define I2S_DOUT 7
#define I2S_BCLK 8
#define I2S_LRCLK 9


typedef struct voice_t {
  WAVFile* wav;
  volatile int16_t play_position;
  float volume;
} Voice_t;

class I2SOutput {
  private:
    TaskHandle_t i2sWriterTask;
    QueueHandle_t i2sQueue;
    std::list<Voice_t> voices;
    I2SClass I2S;
  public:
    void begin();
    void add(WAVFile* file, float volume);

    friend void I2SWriterTask(void* param);
};

#endif // !H_I2SOUTPUT
