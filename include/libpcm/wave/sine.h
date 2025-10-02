#ifndef LIBPCM_WAVE_H
#define LIBPCM_WAVE_H

#include <libpcm/generate.h>
#include <libpcm/types.h>

typedef struct {
  libpcm__rate_hz_t frequency;
  libpcm__amplitude_t amplitude;

  // Current phase in the wave cycle, represented as a float in [0.0, 1.0).
  libpcm__sample_float_t phase;
} libpcm__sine_wave_t;

libpcm__err_t libpcm__sine_wave__init(libpcm__sine_wave_t *wave,
                                      libpcm__rate_hz_t frequency,
                                      libpcm__amplitude_t amplitude);

libpcm__err_t libpcm__sine_wave__generate(libpcm__generate_context_t *ctx,
                                          libpcm__sine_wave_t *wave);

#endif // LIBPCM_WAVE_H