#ifndef LIBPCM_GENERATE_H
#define LIBPCM_GENERATE_H

#include <libpcm/sample.h>
#include <libpcm/types.h>
#include <stddef.h>

typedef struct {
  /* Pointer to the buffer's samples. Each sample is a PCM-encoded audio sample
   * (single channel) */
  libpcm__sample_t *samples;

  /* The length of the buffer's sample, in samples (not necessarily bytes!) */
  size_t len;
} libpcm__sample_buffer_t;

typedef struct {
  /* Sample rate in Hz (e.g., 44100, 48000). */
  libpcm__rate_hz_t sample_rate;

  /* Function to convert float samples to the appropriate PCM format. */
  libpcm__sample_float_to_sample_fn_t float_to_sample;

  /* Buffer to hold generated samples. */
  libpcm__sample_buffer_t buffer;
} libpcm__generate_context_t;

libpcm__err_t
libpcm__generate_context__validate(const libpcm__generate_context_t *ctx);

#endif // LIBPCM_GENERATE_H