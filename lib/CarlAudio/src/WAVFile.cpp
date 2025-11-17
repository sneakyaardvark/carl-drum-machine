/** 
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids
 * Under the Unlicense
 */
#include "WAVFile.hpp"
#include <HardwareSerial.h>
#include <FS.h>
#include <SPIFFS.h>
#include <stdlib.h>
#include "WAVHeader.h"
#include <esp_log.h>

static bool is_header_valid(wav_header_t* header);

WAVFile::WAVFile(const char* filename, size_t frame_size) {
  number_samples = 0;
  samples = NULL;
  fs::FS fs = SPIFFS;
  File file = fs.open(filename);
  if (!file) {
    // failed to open
    return;
  }

  // read header
  wav_header_t header;
  file.read((uint8_t*)&header, sizeof(wav_header_t));
  if (!is_header_valid(&header)) {
    Serial.println("Error: invlaid WAV header");
  }
  else {
    // number_samples = header.data_bytes / (header.bit_depth / 8);
    number_samples = header.data_bytes / sizeof(int16_t);
    samples = (int16_t *)malloc(header.data_bytes);
    size_t bytes_read = file.read((uint8_t *)samples, header.data_bytes);

    if (bytes_read != header.data_bytes) {
      Serial.print("read bytes: ");
      Serial.println(bytes_read);
      Serial.print("total data bytes: ");
      Serial.println(header.data_bytes);
      Serial.println("Error: did not read all samples");
    }
  }

  file.close();
}

int32_t WAVFile::get_number_samples() {
  return number_samples;
}

int16_t WAVFile::get_sample(uint32_t position) {
  return samples[position];
}
union byte_to_u16 {
  struct double_byte {
    uint8_t byte0;
    uint8_t byte1;
  } bytes;
  int16_t u16;
};

// int16_t WAVFile::get_sample2(uint32_t position) {
//   return samples[position];
//   position *= 2;
//   return (samples[position] << 8) | samples[position + 1];
//   // return ((int16_t *) samples)[position];
//   union byte_to_u16 test = {
//     { samples[position], samples[position + 1] }
//   };
//   return test.u16;
// }

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
}
