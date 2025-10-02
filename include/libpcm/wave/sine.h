#ifndef LIBPCM_WAVE_SINE_H
#define LIBPCM_WAVE_SINE_H

#include <libpcm/generate.h>
#include <libpcm/types.h>
#include <libpcm/wave/wave.h>

typedef struct {
  libpcm__wave_t wave;
} libpcm__sine_wave_t;

libpcm__err_t libpcm__sine_wave__init(libpcm__sine_wave_t *sine,
                                      libpcm__rate_hz_t frequency,
                                      libpcm__amplitude_t amplitude);

libpcm__err_t libpcm__sine_wave__generate(libpcm__generate_context_t *ctx,
                                          libpcm__sine_wave_t *sine);

#endif // LIBPCM_WAVE_SINE_H