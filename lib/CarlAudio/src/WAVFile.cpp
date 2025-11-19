/*
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids
 * Under the Unlicense
 */
#include "WAVFile.hpp"
#include <HardwareSerial.h>
#include <FS.h>
#include <SPIFFS.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "WAVHeader.h"
#include "esp_err.h"
#include "i2s_def.h"

static const char *TAG = "WAV";

static bool is_header_valid(wav_header_t* header);

WAVFile::WAVFile(const char* filename, size_t frame_size) {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  number_samples = 0;
  cached_sample_offset = 0;
  samples = NULL;
  fs::FS fs = SPIFFS;
  file = fs.open(filename);
  if (!file) {
    ESP_LOGE(TAG, "failed to open file");
    return;
  }

  // read header
  wav_header_t header;
  file.read((uint8_t*)&header, sizeof(wav_header_t));
  if (!is_header_valid(&header)) {
    Serial.println("Error: invlaid WAV header");
  }
  else {
    total_number_samples = header.data_bytes / sizeof(i2s_sample_t);
    ESP_LOGE(TAG, "total samples = %u", total_number_samples);

    samples = (i2s_sample_t *)malloc(sizeof(i2s_sample_t) * SAMPLE_FRAME_COUNT);
    // load the first frames of samples
    fetch_samples();
  }
}

uint32_t WAVFile::get_number_samples(void) {
  return number_samples;
}

uint32_t WAVFile::get_total_number_samples(void) {
  return total_number_samples;
}

i2s_sample_t WAVFile::get_sample(uint32_t position) {
  ESP_LOGI(TAG, "getting sample @ %u", position);
  ESP_LOGI(TAG, "cached offset = %u", cached_sample_offset);
  if (position >= cached_sample_offset) {
    fetch_samples();
  }
  return samples[position % cached_sample_offset];
}

void WAVFile::fetch_samples(void) {
  ESP_LOGI(TAG, "available bytes:%d", file.available());
  size_t bytes_read = file.read((uint8_t *)samples, sizeof(i2s_sample_t) * SAMPLE_FRAME_COUNT);
  if (bytes_read != sizeof(i2s_sample_t) * SAMPLE_FRAME_COUNT) {
    char buf[64];
    strerror_r(errno, buf, sizeof(buf));
    // esp_err_to_name_r(errno, buf, sizeof(buf));
    ESP_LOGE(TAG, "fetch read error: %s", buf);
  }
  number_samples = bytes_read / sizeof(i2s_sample_t);
  if (number_samples != SAMPLE_FRAME_COUNT) {
    ESP_LOGE(TAG, "number of samples fetched != SAMPLE_FRAME_COUNT (%u != %u)", number_samples, SAMPLE_FRAME_COUNT);
  }
  ESP_LOGI(TAG, "fetched %u samples in %u bytes", number_samples, bytes_read);
  cached_sample_offset += number_samples;
  ESP_LOGI(TAG, "cache offset=%u", cached_sample_offset);
}

static bool is_header_valid(wav_header_t* header) {
  if (header->bit_depth != 16) {
    Serial.println("bit_depth not 16");
    return false;
  } else if (header->audio_format != 1) {
    Serial.println("audio format not PCM");
    return false;
  } else if (header->sample_rate != 48000) {
    Serial.print("sample_rate==");
    Serial.println(header->sample_rate);
    return false;
  }
  return true;
}

WAVFile::~WAVFile() {
  free(samples);
  file.close();
}

void WAVFile::reset(void) {
  file.seek(sizeof(wav_header_t), SeekSet);
  cached_sample_offset = 0;
  fetch_samples();
}
