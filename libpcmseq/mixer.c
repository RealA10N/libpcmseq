#include <libpcmseq/mixer.h>

libpcmseq__err_t
libpcmseq__stereo_mixer__init(libpcmseq__stereo_mixer_t *mixer) {
  if (NULL == mixer) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  mixer->voices = NULL;
  return LIBPCMSEQ__OK;
}

void libpcmseq__stereo_mixer__del(libpcmseq__stereo_mixer_t *mixer) {
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
libpcmseq__stereo_mixer__add_voice(libpcmseq__stereo_mixer_t *mixer,
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

libpcmseq__err_t
libpcmseq__stereo_mixer__mix(libpcmseq__stereo_mixer_t *mixer,
                             libpcmseq__stereo_frame_t *out_frames,
                             size_t out_frames_num) {
  if (NULL == mixer || NULL != mixer->float_to_sample_fn ||
      NULL == out_frames || 0 == out_frames_num) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  for (size_t i = 0; i < out_frames_num; i++) {
    libpcmseq__sample_float_t left = 0.0f, right = 0.0f;
    size_t total_voices = 0;

    // TODO: Optimize to not go over the entire list every time.
    for (libpcmseq__stereo_voice_node_t *voice_node = mixer->voices;
         NULL != voice_node; voice_node = voice_node->next) {
      libpcmseq__stereo_voice_t *voice = &voice_node->voice;
      if (NULL == voice->clip || NULL == voice->clip->frames ||
          voice->next_frame_index >= voice->clip->frames_num) {
        continue;
      }

      left += voice->clip->frames[voice->next_frame_index].left;
      right += voice->clip->frames[voice->next_frame_index].right;
      total_voices++;

      // TODO: Optimize to advance all voices only once after mixing all frames.
      voice->next_frame_index++;
      if (voice->loop) {
        voice->next_frame_index %= voice->clip->frames_num;
      }
    }

    if (total_voices > 0) {
      left /= total_voices;
      right /= total_voices;
    }

    out_frames[i].left = mixer->float_to_sample_fn(left);
    out_frames[i].right = mixer->float_to_sample_fn(right);
  }

  return LIBPCMSEQ__OK;
}
