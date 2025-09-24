#ifndef LIBPCMSEQ_MIXER_H
#define LIBPCMSEQ_MIXER_H

#include <libpcmseq/sample.h>
#include <libpcmseq/voice.h>

typedef struct {
  libpcmseq__stereo_voice_node_t *voices;
  libpcmseq__sample_float_to_sample_fn_t float_to_sample_fn;
} libpcmseq__stereo_mixer_t;

/**
 * @brief Initializes a mixer.
 *
 * @param[in,out] mixer Pointer to the mixer to initialize.
 * @param[in] float_to_sample_fn Function to convert float samples to the
 * desired sample format.
 */
libpcmseq__err_t libpcmseq__stereo_mixer__init(
    libpcmseq__stereo_mixer_t *mixer,
    libpcmseq__sample_float_to_sample_fn_t float_to_sample_fn);

/**
 * @brief Deletes a mixer and frees all associated resources (voices).
 *
 * @param[in,out] mixer Pointer to the mixer to delete.
 */
void libpcmseq__stereo_mixer__del(libpcmseq__stereo_mixer_t *mixer);

/**
 * @brief Adds a voice to the mixer. This allocates memory for the voice node,
 * which will be freed when the mixer is deleted.
 *
 * @param[in,out] mixer Pointer to the mixer.
 * @param[out] voice_id A unique ID of the voice, that can be used afterwards to
 *  modify and control it (e.g., stop it).
 * @param[in] voice The voice to add.
 * @return LIBPCMSEQ__OK on success, or an error code on failure.
 */
libpcmseq__err_t
libpcmseq__stereo_mixer__add_voice(libpcmseq__stereo_mixer_t *mixer,
                                   libpcmseq__stereo_voice_id_t *voice_id,
                                   libpcmseq__stereo_voice_t voice);

/**
 * @brief Removes a voice from the mixer, and deallocates its resources.
 *
 * @param[in,out] mixer Pointer to the mixer.
 * @param[in] voice_id The ID of the voice to remove.
 * @return LIBPCMSEQ__OK on success, or an error code on failure.
 */
libpcmseq__err_t
libpcmseq__stereo_mixer__remove_voice(libpcmseq__stereo_mixer_t *mixer,
                                      libpcmseq__stereo_voice_id_t voice_id);

/**
 * @brief Mixes all active voices into the output buffer.
 *
 * Each frame in the output buffer is the average of all active voices' frames.
 * TODO: make this more sophisticated (e.g., volume control, panning, etc.)
 *
 * @param[in] mixer Pointer to the mixer.
 * @param[out] out_frames Pointer to the output buffer where mixed frames will
 * be stored.
 * @param[in] out_frames_num Number of frames to mix into the output buffer.
 * @return LIBPCMSEQ__OK on success, or an error code on failure.
 */
libpcmseq__err_t
libpcmseq__stereo_mixer__mix(libpcmseq__stereo_mixer_t *mixer,
                             libpcmseq__stereo_frame_t *out_frames,
                             size_t out_frames_num);

#endif // LIBPCMSEQ_MIXER_H
