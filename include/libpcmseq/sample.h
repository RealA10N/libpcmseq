#ifndef LIBPCMSEQ_SAMPLE_H
#define LIBPCMSEQ_SAMPLE_H

#include <stdint.h>

typedef int16_t libpcmseq__sample_t;
typedef float libpcmseq__sample_float_t;

typedef libpcmseq__sample_t (*libpcmseq__sample_float_to_sample_fn_t)(
    libpcmseq__sample_float_t);

/**
 * @brief Converts a floating-point sample to an integer sample, clipping
 *  values that are out of range.
 *
 * @param[in] sample The floating-point sample to convert.
 * @return The converted integer sample, clipped to the valid range.
 */
libpcmseq__sample_t
libpcmseq__sample_float_to_sample__clip(libpcmseq__sample_float_t sample);

#endif // LIBPCMSEQ_SAMPLE_H