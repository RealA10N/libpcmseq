#include <stdbool.h>
#include <stdint.h>

typedef enum {
  LIBPCMSEQ__OK = 0,
  LIBPCMSEQ__FAILURE = 1,
  LIBPCMSEQ__ERR_INVALID_ARG,
  LIBPCMSEQ__ERR_NO_MEMORY,
} libpcmseq__err_t;

typedef int16_t libpcmseq__sample_t;
typedef int16_t libpcmseq__amplitude_t; // Assumed to be positive.
typedef uint32_t libpcmseq__rate_hz_t;

// A frame is a single sample for each channel - a complete sample for a unique
// point in time.
typedef struct {
  libpcmseq__sample_t left;
  libpcmseq__sample_t right;
} libpcmseq__stereo_frame_t;

// A clip is a sequence of frames at a specific sample rate.
typedef struct {
  libpcmseq__stereo_frame_t *frames;
  size_t frames_num;
  libpcmseq__rate_hz_t sample_rate;
} libpcmseq__stereo_clip_t;

// A voice is a clip being played, with a current position.
typedef struct {
  libpcmseq__stereo_clip_t *clip;
  size_t next_frame_index;
  // If true, when the end of the clip is reached, playback restarts from the
  // beginning. If false, playback stops at the end of the clip.
  bool loop;
} libpcmseq__stereo_voice_t;
