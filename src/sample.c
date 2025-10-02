#include <libpcm/sample.h>

libpcm__sample_t
libpcm__sample_float_to_sample__clip(libpcm__sample_float_t sample) {
  if (sample > (libpcm__sample_float_t)INT16_MAX) {
    return (libpcm__sample_t)INT16_MAX;
  } else if (sample < (libpcm__sample_float_t)INT16_MIN) {
    return (libpcm__sample_t)INT16_MIN;
  } else {
    return (libpcm__sample_t)sample;
  }
}
