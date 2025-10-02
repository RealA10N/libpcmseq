#include <libpcm/generate.h>

libpcm__err_t
libpcm__generate_context__validate(const libpcm__generate_context_t *ctx) {
  if (NULL == ctx || 0 == ctx->sample_rate || NULL == ctx->float_to_sample ||
      NULL == ctx->buffer.samples || 0 == ctx->buffer.len) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  return LIBPCM__OK;
}
