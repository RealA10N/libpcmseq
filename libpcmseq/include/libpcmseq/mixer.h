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

#endif // LIBPCMSEQ_MIXER_H
