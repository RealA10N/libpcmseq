#include <libpcm/mixer.h>

#include <stdlib.h>

libpcm__err_t libpcm__stereo_mixer__init(
    libpcm__stereo_mixer_t *mixer,
    libpcm__sample_float_to_sample_fn_t float_to_sample_fn) {
  if (NULL == mixer || NULL == float_to_sample_fn) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  mixer->voices = NULL;
  mixer->float_to_sample_fn = float_to_sample_fn;
  return LIBPCM__OK;
}

void libpcm__stereo_mixer__del(libpcm__stereo_mixer_t *mixer) {
  if (NULL == mixer) {
    return;
  }

  libpcm__stereo_voice_node_t *current = mixer->voices;
  while (NULL != current) {
    libpcm__stereo_voice_node_t *next = current->next;
    free(current);
    current = next;
  }

  mixer->voices = NULL;
}

libpcm__err_t
libpcm__stereo_mixer__add_voice(libpcm__stereo_mixer_t *mixer,
                                libpcm__stereo_voice_id_t *voice_id,
                                libpcm__stereo_voice_t voice) {
  if (NULL == mixer || NULL == voice.clip) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  libpcm__stereo_voice_node_t *voice_node =
      malloc(sizeof(libpcm__stereo_voice_node_t));
  if (NULL == voice_node) {
    return LIBPCM__ERR_NO_MEMORY;
  }

  *voice_node = (libpcm__stereo_voice_node_t){
      .voice = voice,
      .next = mixer->voices,
  };

  mixer->voices = voice_node;

  if (NULL != voice_id) {
    *voice_id = (libpcm__stereo_voice_id_t)voice_node;
  }

  return LIBPCM__OK;
}

libpcm__err_t
libpcm__stereo_mixer__remove_voice(libpcm__stereo_mixer_t *mixer,
                                   libpcm__stereo_voice_id_t voice_id) {
  if (NULL == mixer || NULL == voice_id) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  libpcm__stereo_voice_node_t *prev = NULL;
  libpcm__stereo_voice_node_t *current = mixer->voices;
  while (NULL != current) {
    if (current == (libpcm__stereo_voice_node_t *)voice_id) {
      if (NULL == prev) {
        mixer->voices = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return LIBPCM__OK;
    }
    prev = current;
    current = current->next;
  }

  return LIBPCM__ERR_NOT_FOUND;
}

libpcm__err_t libpcm__stereo_mixer__mix(libpcm__stereo_mixer_t *mixer,
                                        libpcm__stereo_frame_t *out_frames,
                                        size_t out_frames_num) {
  if (NULL == mixer || NULL == mixer->float_to_sample_fn ||
      NULL == out_frames || 0 == out_frames_num) {
    return LIBPCM__ERR_INVALID_ARG;
  }

  for (size_t i = 0; i < out_frames_num; i++) {
    libpcm__sample_float_t left = 0.0f, right = 0.0f;

    // TODO: Optimize to not go over the entire list every time.
    for (libpcm__stereo_voice_node_t *voice_node = mixer->voices;
         NULL != voice_node; voice_node = voice_node->next) {
      libpcm__stereo_voice_t *voice = &voice_node->voice;
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

  return LIBPCM__OK;
}
