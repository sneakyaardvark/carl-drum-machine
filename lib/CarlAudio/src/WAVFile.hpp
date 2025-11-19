/*
 * parts of this file are derived from https://github.com/atomic14/esp-asteroids
 * Under the Unlicense
 */
/**
 * @file WAVFile.hpp
 * @brief WAV file object
 */
#ifndef H_WAVFILE
#define H_WAVFILE

#include "i2s_def.h"
#include <stdint.h>
#include <stddef.h>
#include <FS.h>
#define SAMPLE_FRAME_COUNT 48000

/**
 * @brief a WAV file.
 */
class WAVFile {
  private:
    i2s_sample_t* samples; /**< the samples cached for this file */
    uint32_t number_samples; /**< the number of samples cached for this file */
    uint32_t total_number_samples;
    uint32_t cached_sample_offset;
    File file;

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
    i2s_sample_t get_sample(uint32_t position);
    /**
     * @brief get the number of samples
     *
     * If the sample at position is not available in the cached samples,
     * a blocking acion is started to fetch the next set of samples.
     * @see fetch_samples()
     * @param position the position of the sample
     * @return the number of samples
     */
    uint32_t get_number_samples(void);
    /** 
     * @brief get the total number of samples in the WAV
     * @returns the number of samples
     */
    uint32_t get_total_number_samples(void);

    /**
     * @brief initiate a fetch of new samples into memory
     * The samples will overwrite the samples array.
     */
    void fetch_samples(void);
    /**
     * @brief reset this WAV back to initial state, so it can be replayed.
     */
    void reset(void);
};

#endif // !H_WAVFILE
