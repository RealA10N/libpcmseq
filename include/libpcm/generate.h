#ifndef LIBPCM_GENERATE_H
#define LIBPCM_GENERATE_H

#include <libpcm/sample.h>
#include <libpcm/types.h>
#include <stddef.h>

typedef struct {
  libpcm__sample_t *samples;
  size_t size;
} libpcm__sample_buffer_t;

typedef struct {
  libpcm__rate_hz_t sample_rate;
  libpcm__sample_float_to_sample_fn_t float_to_sample;
  libpcm__sample_buffer_t buffer;
  size_t position;
} libpcm__generate_context_t;

libpcm__err_t
libpcm__generate_context__validate(const libpcm__generate_context_t *ctx);

#endif // LIBPCM_GENERATE_H