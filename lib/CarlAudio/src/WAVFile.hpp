#ifndef H_WAVFILE
#define H_WAVFILE

#include <cstdint>
#include <stdint.h>
#include <stddef.h>

class WAVFile {
  private:
    uint16_t* samples;
    int16_t number_samples;

  public:
    WAVFile(const char* filename, size_t frame_size);
    ~WAVFile();
    uint16_t get_sample(int16_t position);
    int16_t get_number_samples();
};

#endif // !H_WAVFILE
