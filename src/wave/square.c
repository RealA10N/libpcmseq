#include <libpcm/wave/square.h>

libpcm__err_t libpcm__square_wave__init(libpcm__square_wave_t *square,
                                        libpcm__rate_hz_t frequency,
                                        libpcm__amplitude_t amplitude) {
  if (NULL == square) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  return libpcm__wave__init(&square->wave, frequency, amplitude);
}

libpcm__err_t libpcm__square_wave__generate(libpcm__generate_context_t *ctx,
                                            libpcm__square_wave_t *square) {
  if (NULL == ctx || NULL == square) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  libpcm__sample_t phase_increment = square->wave.frequency / ctx->sample_rate;

  for (size_t i = 0; i < ctx->buffer.len; i++) {
    float sample = (square->wave.phase < 0.5f) ? square->wave.amplitude
                                               : -square->wave.amplitude;
    ctx->buffer.samples[i] = ctx->float_to_sample(sample);

    square->wave.phase += phase_increment;
    while (square->wave.phase >= 1.0f) {
      square->wave.phase -= 1.0f;
    }
  }

  return LIBPCM__OK;
}