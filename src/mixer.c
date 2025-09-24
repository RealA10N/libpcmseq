#include <libpcmseq/mixer.h>

#include <stdlib.h>

libpcmseq__err_t libpcmseq__stereo_mixer__init(
    libpcmseq__stereo_mixer_t *mixer,
    libpcmseq__sample_float_to_sample_fn_t float_to_sample_fn) {
  if (NULL == mixer || NULL == float_to_sample_fn) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  mixer->voices = NULL;
  mixer->float_to_sample_fn = float_to_sample_fn;
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
}

libpcmseq__err_t
libpcmseq__stereo_mixer__add_voice(libpcmseq__stereo_mixer_t *mixer,
                                   libpcmseq__stereo_voice_id_t *voice_id,
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

  if (NULL != voice_id) {
    *voice_id = (libpcmseq__stereo_voice_id_t)voice_node;
  }

  return LIBPCMSEQ__OK;
}

libpcmseq__err_t
libpcmseq__stereo_mixer__remove_voice(libpcmseq__stereo_mixer_t *mixer,
                                      libpcmseq__stereo_voice_id_t voice_id) {
  if (NULL == mixer || NULL == voice_id) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  libpcmseq__stereo_voice_node_t *prev = NULL;
  libpcmseq__stereo_voice_node_t *current = mixer->voices;
  while (NULL != current) {
    if (current == (libpcmseq__stereo_voice_node_t *)voice_id) {
      if (NULL == prev) {
        mixer->voices = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return LIBPCMSEQ__OK;
    }
    prev = current;
    current = current->next;
  }

  return LIBPCMSEQ__ERR_NOT_FOUND;
}

libpcmseq__err_t
libpcmseq__stereo_mixer__mix(libpcmseq__stereo_mixer_t *mixer,
                             libpcmseq__stereo_frame_t *out_frames,
                             size_t out_frames_num) {
  if (NULL == mixer || NULL == mixer->float_to_sample_fn ||
      NULL == out_frames || 0 == out_frames_num) {
    return LIBPCMSEQ__ERR_INVALID_ARG;
  }

  for (size_t i = 0; i < out_frames_num; i++) {
    libpcmseq__sample_float_t left = 0.0f, right = 0.0f;

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

      // TODO: Optimize to advance all voices only once after mixing all frames.
      voice->next_frame_index++;
      if (voice->loop) {
        voice->next_frame_index %= voice->clip->frames_num;
      }
    }

    out_frames[i].left = mixer->float_to_sample_fn(left);
    out_frames[i].right = mixer->float_to_sample_fn(right);
  }

  return LIBPCMSEQ__OK;
}
