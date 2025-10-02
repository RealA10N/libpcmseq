#include <libpcm/wave/sine.h>
#include <math.h>
#include <stddef.h>

libpcm__err_t libpcm__sine_wave__init(libpcm__sine_wave_t *sine,
                                      libpcm__rate_hz_t frequency,
                                      libpcm__amplitude_t amplitude) {
  if (NULL == sine) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  return libpcm__wave__init(&sine->wave, frequency, amplitude);
}

libpcm__err_t libpcm__sine_wave__generate(libpcm__generate_context_t *ctx,
                                          libpcm__sine_wave_t *sine) {
  if (NULL == ctx || NULL == sine) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  libpcm__sample_float_t phase_increment =
      sine->wave.frequency / ctx->sample_rate;

  for (size_t i = 0; i < ctx->buffer.len; i++) {
    libpcm__sample_float_t sample =
        sine->wave.amplitude * sinf(2.0f * M_PI * sine->wave.phase);
    ctx->buffer.samples[i] = ctx->float_to_sample(sample);

    sine->wave.phase += phase_increment;
  }

  // TODO: check if this while loop is faster than fmodf.
  while (sine->wave.phase >= 1.0f) {
    sine->wave.phase -= 1.0f;
  }

  return LIBPCM__OK;
}
