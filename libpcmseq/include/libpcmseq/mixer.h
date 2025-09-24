#ifndef LIBPCMSEQ_MIXER_H
#define LIBPCMSEQ_MIXER_H

#include <libpcmseq/voice.h>

typedef struct {
  libpcmseq__stereo_voice_t voice;
  libpcmseq__stereo_voice_node_t *next;
} libpcmseq__stereo_voice_node_t;

typedef struct {
  libpcmseq__stereo_voice_node_t *voices;
} libpcmseq__mixer_t;

/**
 * @brief Initializes a mixer.
 *
 * @param[in,out] mixer Pointer to the mixer to initialize.
 */
libpcmseq__err_t libpcmseq__mixer__init(libpcmseq__mixer_t *mixer);

/**
 * @brief Deletes a mixer and frees all associated resources (voices).
 *
 * @param[in,out] mixer Pointer to the mixer to delete.
 */
void libpcmseq__mixer__del(libpcmseq__mixer_t *mixer);

/**
 * @brief Adds a voice to the mixer. This allocates memory for the voice node,
 * which will be freed when the mixer is deleted.
 *
 * @param[in,out] mixer Pointer to the mixer.
 * @param[in] voice The voice to add.
 * @return LIBPCMSEQ__OK on success, or an error code on failure.
 */
libpcmseq__err_t libpcmseq__mixer__add_voice(libpcmseq__mixer_t *mixer,
                                             libpcmseq__stereo_voice_t voice);

#endif // LIBPCMSEQ_MIXER_H
