#ifndef LIBPCMSEQ_VOICE_H
#define LIBPCMSEQ_VOICE_H

#include <libpcmseq/clip.h>
#include <libpcmseq/types.h>

#include <stdbool.h>

// A voice is a clip being played, with a current position.
typedef struct {
  libpcmseq__stereo_clip_t *clip;
  size_t next_frame_index;
  // If true, when the end of the clip is reached, playback restarts from the
  // beginning. If false, playback stops at the end of the clip.
  bool loop;
} libpcmseq__stereo_voice_t;

typedef struct {
  libpcmseq__stereo_voice_t voice;
  libpcmseq__stereo_voice_node_t *next;
} libpcmseq__stereo_voice_node_t;

// Internally, a voice ID is a pointer to the voice node in the mixer.
typedef libpcmseq__stereo_voice_node_t *libpcmseq__stereo_voice_id_t;

/**
 * @brief Initializes a stereo voice with the given clip and settings.
 *
 * @param[out] voice Pointer to the voice to initialize.
 * @param[in] clip Pointer to the clip to be played by the voice.
 * @param[in] loop If true, the voice will loop the clip when it reaches the
 * end. If false, playback will stop at the end of the clip.
 */
libpcmseq__err_t libpcmseq__stereo_voice__init(libpcmseq__stereo_voice_t *voice,
                                               libpcmseq__stereo_clip_t *clip,
                                               bool loop);

#endif // LIBPCMSEQ_VOICE_H