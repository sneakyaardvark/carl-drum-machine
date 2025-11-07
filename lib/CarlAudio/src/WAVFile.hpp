/*
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids
 * Under the Unlicense
 */
#ifndef H_WAVFILE
#define H_WAVFILE

#include <stdint.h>
#include <stddef.h>

/**
 * @brief a WAV file.
 */
class WAVFile {
  private:
    uint8_t* samples; /**< the samples cached for this file */
    int16_t number_samples; /**< the number of samples cached for this file */

  public:
    /**
     * @brief Create a WAVFile from filename with caching frame size frame_size
     * @param filename the name of the file to load
     * @param frame_size the size of the sample cache
     */
    WAVFile(const char* filename, size_t frame_size);
    ~WAVFile();
    /**
     * @brief get a sample
     * @param position which sample to get
     * @return the sample
     */
    uint8_t get_sample(int16_t position);
    /**
     * @brief get the number of samples
     * @return the number of samples
     */
    int16_t get_number_samples();
};

#endif // !H_WAVFILE
