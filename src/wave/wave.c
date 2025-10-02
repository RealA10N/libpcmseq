#include <libpcm/wave/sine.h>
#include <math.h>
#include <stddef.h>

libpcm__err_t libpcm__sine_wave__init(libpcm__wave_t *wave,
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
