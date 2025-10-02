#include <libpcm/clip.h>
#include <libpcm/voice.h>

#include <stdbool.h>
#include <stddef.h>

libpcm__err_t libpcm__stereo_voice__init(libpcm__stereo_voice_t *voice,
                                         libpcm__stereo_clip_t *clip,
                                         bool loop) {
  if (NULL == voice || NULL == clip) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  *voice = (libpcm__stereo_voice_t){
      .clip = clip, .next_frame_index = 0, .loop = loop};

  return LIBPCM__OK;
}
