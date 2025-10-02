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
  libpcm__err_t err = libpcm__generate_context__validate(ctx);
  if (LIBPCM__OK != err) {
    return err;
  }

  if (NULL == sine) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  uint32_t samples_per_cycle = ctx->sample_rate / sine->wave.frequency;
  if (samples_per_cycle <= 1) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  uint32_t phase_increment = samples_per_cycle / sine->wave.amplitude;

  while (ctx->position < ctx->buffer.len) {
    libpcm__sample_float_t sample =
        sine->wave.amplitude * sinf(2.0f * M_PI * sine->wave.phase);
    ctx->buffer.samples[ctx->position++] = ctx->float_to_sample(sample);

    sine->wave.phase += phase_increment;
  }

  // TODO: check if this while loop is faster than fmodf.
  while (sine->wave.phase >= 1.0f) {
    sine->wave.phase -= 1.0f;
  }

  return LIBPCM__OK;
}
