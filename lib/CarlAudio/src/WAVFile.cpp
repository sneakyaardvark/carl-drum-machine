/** 
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids
 * Under the Unlicense
 */
#include "WAVFile.hpp"
#include <HardwareSerial.h>
#include <FS.h>
#include <SPIFFS.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct wav_header {
  char riff_header[4];
  int32_t wav_size; // size of the wav portion - File size - 8
  char wave_header[4]; // contains "WAVE"

  char fmt_header[4]; // contains "fmt "
  int32_t fmt_chunk_size; // 16 for pcm
  uint16_t audio_format;   // Should be 1 for PCM. 3 for IEEE Float
  uint16_t num_channels;
  uint32_t sample_rate;
  uint32_t byte_rate;        // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
  uint16_t sample_alignment; // num_channels * Bytes Per Sample
  uint16_t bit_depth;        // Number of bits per sample

  // Data
  char data_header[4]; // Contains "data"
  uint32_t data_bytes;  // Number of bytes in data. Number of samples * num_channels * sample byte size
} wav_header_t;
#pragma pack(pop)

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

int16_t WAVFile::get_number_samples() {
  return number_samples;
}

uint8_t WAVFile::get_sample(uint32_t position) {
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
