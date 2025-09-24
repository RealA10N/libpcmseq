#ifndef LIBPCMSEQ_CLIP_H
#define LIBPCMSEQ_CLIP_H

#include <libpcmseq/types.h>

#include <stddef.h>

// A frame is a single sample for each channel - a complete sample for a unique
// point in time.
typedef struct {
  libpcmseq__sample_t left;
  libpcmseq__sample_t right;
} libpcmseq__stereo_frame_t;

// A clip is a sequence of frames at a specific sample rate.
typedef struct {
  libpcmseq__stereo_frame_t *frames;
  size_t frames_num;
  libpcmseq__rate_hz_t sample_rate;
} libpcmseq__stereo_clip_t;

/**
 * @brief Initializes a stereo clip. Allocates memory for the frames.
 *
 * @param[out] clip Pointer to the clip to initialize.
 * @param[in] frames_num Number of frames in the clip. Must be greater than 0.
 * @param[in] sample_rate Sample rate of the clip.
 */
libpcmseq__err_t libpcmseq__stereo_clip__init(libpcmseq__stereo_clip_t *clip,
                                              size_t frames_num,
                                              libpcmseq__rate_hz_t sample_rate);

/**
 * @brief Deallocates memory used by the clip and resets its fields.
 *
 * @param[in,out] clip Pointer to the clip to delete.
 */
void libpcmseq__stereo_clip__del(libpcmseq__stereo_clip_t *clip);

/**
 * @brief Initializes a stereo clip with a square wave.
 *
 * The clip will contain one period of the square wave.
 *
 * @param[out] clip Pointer to the clip to initialize.
 * @param[in] sample_rate Sample rate of the clip.
 * @param[in] amplitude Amplitude of the square wave.
 * @param[in] freq_hz Frequency of the square wave in Hz.
 */
libpcmseq__err_t libpcmseq__stereo_clip__init_square_wave(
    libpcmseq__stereo_clip_t *clip, libpcmseq__rate_hz_t sample_rate,
    libpcmseq__amplitude_t amplitude, libpcmseq__rate_hz_t freq_hz);

#endif // LIBPCMSEQ_CLIP_H