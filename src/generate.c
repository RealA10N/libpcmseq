#include <libpcm/generate.h>

libpcm__err_t
libpcm__generate_context__validate(const libpcm__generate_context_t *ctx) {
  if (NULL == ctx || NULL == ctx->buffer.samples || ctx->buffer.size == 0) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  return LIBPCM__OK;
}
