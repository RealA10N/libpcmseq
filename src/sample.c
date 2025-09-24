#include <libpcmseq/sample.h>

libpcmseq__sample_t
libpcmseq__sample_float_to_sample__clip(libpcmseq__sample_float_t sample) {
  if (sample > (libpcmseq__sample_float_t)INT16_MAX) {
    return (libpcmseq__sample_t)INT16_MAX;
  } else if (sample < (libpcmseq__sample_float_t)INT16_MIN) {
    return (libpcmseq__sample_t)INT16_MIN;
  } else {
    return (libpcmseq__sample_t)sample;
  }
}
