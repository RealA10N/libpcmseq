#ifndef LIBPCM_WAVE_SQUARE_H
#define LIBPCM_WAVE_SQUARE_H

#include <libpcm/generate.h>
#include <libpcm/types.h>
#include <libpcm/wave/wave.h>

typedef struct {
  libpcm__wave_t wave;
} libpcm__square_wave_t;

libpcm__err_t libpcm__square_wave__init(libpcm__square_wave_t *square,
                                        libpcm__rate_hz_t frequency,
                                        libpcm__amplitude_t amplitude);

libpcm__err_t libpcm__square_wave__generate(libpcm__generate_context_t *ctx,
                                            libpcm__square_wave_t *square);

#endif // LIBPCM_WAVE_SQUARE_H