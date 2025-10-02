#ifndef LIBPCM_SAMPLE_H
#define LIBPCM_SAMPLE_H

#include <stdint.h>

typedef int16_t libpcm__sample_t;
typedef float libpcm__sample_float_t;

typedef libpcm__sample_t (*libpcm__sample_float_to_sample_fn_t)(
    libpcm__sample_float_t);

/**
 * @brief Converts a floating-point sample to an integer sample, clipping
 *  values that are out of range.
 *
 * @param[in] sample The floating-point sample to convert.
 * @return The converted integer sample, clipped to the valid range.
 */
libpcm__sample_t
libpcm__sample_float_to_sample__clip(libpcm__sample_float_t sample);

#endif // LIBPCM_SAMPLE_H