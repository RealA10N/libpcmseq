#include <libpcm/wave/sine.h>
#include <math.h>
#include <stddef.h>
libpcm__err_t libpcm__sine_wave__init(libpcm__sine_wave_t *wave,
                                      libpcm__rate_hz_t frequency,
                                      libpcm__amplitude_t amplitude) {
  if (NULL == wave || amplitude <= 0) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  wave->frequency = frequency;
  wave->amplitude = amplitude;
  wave->phase = 0.0f;

  return LIBPCM__OK;
}

libpcm__err_t libpcm__sine_wave__generate(libpcm__generate_context_t *ctx,
                                          libpcm__sine_wave_t *wave) {
  libpcm__err_t err = libpcm__generate_context__validate(ctx);
  if (LIBPCM__OK != err) {
    return err;
  }

  if (NULL == wave) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  uint32_t samples_per_cycle = ctx->sample_rate / wave->frequency;
  if (samples_per_cycle <= 1) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  uint32_t phase_increment = samples_per_cycle / wave->amplitude;

  while (ctx->position < ctx->buffer.size) {
    libpcm__sample_float_t sample =
        wave->amplitude * sinf(2.0f * M_PI * wave->phase);
    ctx->buffer.samples[ctx->position++] = ctx->float_to_sample(sample);

    wave->phase += phase_increment;
    while (wave->phase >= 1.0f) {
      wave->phase -= 1.0f;
    }
  }

  return LIBPCM__OK;
}