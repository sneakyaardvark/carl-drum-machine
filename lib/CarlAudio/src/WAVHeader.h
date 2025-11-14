/**
 * @file WAVHeader.h
 * @brief Definitions for the WAV file format headers.
 * @author atomic14 <https://github.com/atomic14>, Andrew Stanton <stan35@pdx.edu>
 */
#pragma once
#include <stdint.h>

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

