#include <libpcmseq/clip.h>
#include <libpcmseq/voice.h>

#include <stdbool.h>
#include <stddef.h>

libpcmseq__err_t libpcmseq__stereo_voice__init(libpcmseq__stereo_voice_t *voice,
                                               libpcmseq__stereo_clip_t *clip,
                                               bool loop) {
  if (NULL == voice || NULL == clip) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  *voice = (libpcmseq__stereo_voice_t){
      .clip = clip, .next_frame_index = 0, .loop = loop};

  return LIBPCMSEQ__OK;
}
