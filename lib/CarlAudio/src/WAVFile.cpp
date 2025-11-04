#include "WAVFile.hpp"
#include <FS.h>
#include <SPIFFS.h>

#pragma pack(push, 1)
typedef struct wav_header {
  char riff_header[4];
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
  file.read(&header, sizeof(wav_header_t));
  if (!is_header_valid(&header)) {
    // err: invalid WAV
  }
  else {
    // read first frame of samples

    // returns size_t for # of bytes, might want to store how large the buffer is
    // for playback
    file.read(&samples, frame_size * 2);
  }

  file.close();
}

int16_t WAVFile::get_number_samples() {
  return number_samples;
}

uint16_t WAVFile::get_sample(int16_t position) {
  return samples[position];
}

static bool is_header_valid(wav_header_t* header) {
  // TODO: check validity: bit_depth == 16, etc
  return true;
}
