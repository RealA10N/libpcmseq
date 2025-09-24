#ifndef LIBPCMSEQ_TYPES_H
#define LIBPCMSEQ_TYPES_H

#include <stdint.h>

typedef enum {
  LIBPCMSEQ__OK = 0,
  LIBPCMSEQ__FAILURE = 1,
  LIBPCMSEQ__ERR_INVALID_ARG,
  LIBPCMSEQ__ERR_NO_MEMORY,
  LIBPCMSEQ__ERR_NOT_FOUND,
} libpcmseq__err_t;

typedef int16_t libpcmseq__amplitude_t;
typedef uint32_t libpcmseq__rate_hz_t;

#endif // LIBPCMSEQ_TYPES_H