#include <libpcmseq/clip.h>

#include <stddef.h>
#include <stdlib.h>

libpcmseq__err_t libpcmseq__stereo_clip__init(libpcmseq__stereo_clip_t *clip,
                                              size_t frames_num) {
  if (NULL == clip || 0 == frames_num) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  clip->frames = malloc(frames_num * sizeof(libpcmseq__stereo_frame_t));
  if (NULL == clip->frames) {
    return LIBPCMSEQ__ERR_NO_MEMORY;
  }

  clip->frames_num = frames_num;

  return LIBPCMSEQ__OK;
}

void libpcmseq__stereo_clip__del(libpcmseq__stereo_clip_t *clip) {
  if (NULL == clip) {
    return;
  }

  free(clip->frames);
  clip->frames = NULL;
  clip->frames_num = 0;
}

libpcmseq__err_t libpcmseq__stereo_clip__init_square_wave(
    libpcmseq__stereo_clip_t *clip, libpcmseq__rate_hz_t sample_rate,
    libpcmseq__amplitude_t amplitude, libpcmseq__rate_hz_t freq_hz) {
  libpcmseq__err_t err = LIBPCMSEQ__FAILURE;

  if (NULL == clip) {
    err = LIBPCMSEQ__ERR_INVALID_ARG;
    goto cleanup;
  }

  const size_t frames_num = sample_rate / freq_hz;
  err = libpcmseq__stereo_clip__init(clip, frames_num);
  if (LIBPCMSEQ__OK != err) {
    goto cleanup;
  }

  // TODO: Optimize using memset?

  size_t half_period_size = frames_num / 2;
  for (size_t i = 0; i < half_period_size; i++) {
    clip->frames[i].left = amplitude;
    clip->frames[i].right = amplitude;
  }

  size_t second_half_size = frames_num - half_period_size;
  for (size_t i = half_period_size; i < frames_num; i++) {
    clip->frames[i].left = -amplitude;
    clip->frames[i].right = -amplitude;
  }

  err = LIBPCMSEQ__OK;

cleanup:
  if (LIBPCMSEQ__OK != err) {
    libpcmseq__stereo_clip__del(clip);
  }
  return err;
}
