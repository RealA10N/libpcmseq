#include <libpcm/clip.h>

#include <stddef.h>
#include <stdlib.h>

libpcm__err_t libpcm__stereo_clip__init(libpcm__stereo_clip_t *clip,
                                        size_t frames_num) {
  if (NULL == clip || 0 == frames_num) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  clip->frames = malloc(frames_num * sizeof(libpcm__stereo_frame_t));
  if (NULL == clip->frames) {
    return LIBPCM__ERR_NO_MEMORY;
  }

  clip->frames_num = frames_num;

  return LIBPCM__OK;
}

void libpcm__stereo_clip__del(libpcm__stereo_clip_t *clip) {
  if (NULL == clip) {
    return;
  }

  free(clip->frames);
  clip->frames = NULL;
  clip->frames_num = 0;
}

libpcm__err_t libpcm__stereo_clip__init_square_wave(
    libpcm__stereo_clip_t *clip, libpcm__rate_hz_t sample_rate,
    libpcm__amplitude_t amplitude, libpcm__rate_hz_t freq_hz) {
  libpcm__err_t err = LIBPCM__FAILURE;

  if (NULL == clip) {
    err = LIBPCM__ERR_INVALID_ARG;
    goto cleanup;
  }

  const size_t frames_num = sample_rate / freq_hz;
  err = libpcm__stereo_clip__init(clip, frames_num);
  if (LIBPCM__OK != err) {
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

  err = LIBPCM__OK;

cleanup:
  if (LIBPCM__OK != err) {
    libpcm__stereo_clip__del(clip);
  }
  return err;
}
