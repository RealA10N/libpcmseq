#ifndef LIBPCM_CLIP_H
#define LIBPCM_CLIP_H

#include <libpcm/sample.h>
#include <libpcm/types.h>

#include <stddef.h>

// A frame is a single sample for each channel - a complete sample for a unique
// point in time.
typedef struct {
  libpcm__sample_t left;
  libpcm__sample_t right;
} libpcm__stereo_frame_t;

// A clip is a sequence of frames at a specific sample rate.
typedef struct {
  libpcm__stereo_frame_t *frames;
  size_t frames_num;
} libpcm__stereo_clip_t;

/**
 * @brief Initializes a stereo clip. Allocates memory for the frames.
 *
 * @param[out] clip Pointer to the clip to initialize.
 * @param[in] frames_num Number of frames in the clip. Must be greater than 0.
 * @param[in] sample_rate Sample rate of the clip.
 */
libpcm__err_t libpcm__stereo_clip__init(libpcm__stereo_clip_t *clip,
                                        size_t frames_num);

/**
 * @brief Deallocates memory used by the clip and resets its fields.
 *
 * @param[in,out] clip Pointer to the clip to delete.
 */
void libpcm__stereo_clip__del(libpcm__stereo_clip_t *clip);

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
libpcm__err_t libpcm__stereo_clip__init_square_wave(
    libpcm__stereo_clip_t *clip, libpcm__rate_hz_t sample_rate,
    libpcm__amplitude_t amplitude, libpcm__rate_hz_t freq_hz);

#endif // LIBPCM_CLIP_H