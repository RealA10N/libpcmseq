#ifndef LIBPCM_TYPES_H
#define LIBPCM_TYPES_H

#include <stdint.h>

typedef enum {
  LIBPCM__OK = 0,
  LIBPCM__FAILURE = 1,
  LIBPCM__ERR_INVALID_ARG,
  LIBPCM__ERR_NO_MEMORY,
  LIBPCM__ERR_NOT_FOUND,
} libpcm__err_t;

typedef int16_t libpcm__amplitude_t;
typedef uint32_t libpcm__rate_hz_t;

#endif // LIBPCM_TYPES_H