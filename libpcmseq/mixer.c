#include <libpcmseq/mixer.h>

libpcmseq__err_t libpcmseq__mixer__init(libpcmseq__mixer_t *mixer) {
  if (NULL == mixer) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  mixer->voices = NULL;
  return LIBPCMSEQ__OK;
}

void libpcmseq__mixer__del(libpcmseq__mixer_t *mixer) {
  if (NULL == mixer) {
    return;
  }

  libpcmseq__stereo_voice_node_t *current = mixer->voices;
  while (NULL != current) {
    libpcmseq__stereo_voice_node_t *next = current->next;
    free(current);
    current = next;
  }

  mixer->voices = NULL;
  return LIBPCMSEQ__OK;
}

libpcmseq__err_t
libpcmseq__mixer__append_voice(libpcmseq__mixer_t *mixer,
                               libpcmseq__stereo_voice_t voice) {
  if (NULL == mixer || NULL == voice.clip) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  libpcmseq__stereo_voice_node_t *voice_node =
      malloc(sizeof(libpcmseq__stereo_voice_node_t));
  if (NULL == voice_node) {
    return LIBPCMSEQ__ERR_NO_MEMORY;
  }

  *voice_node = (libpcmseq__stereo_voice_node_t){
      .voice = voice,
      .next = mixer->voices,
  };

  mixer->voices = voice_node;

  return LIBPCMSEQ__OK;
}
