#ifndef AUDIO_H
#define AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define SAMPLE_RATE 96000 /* Sample rate we want the device to accept. */
#define CHANNELS    2     /* 1 = mono, 2 = stereo. */
#define SAMPLES     2048  /* Samples per function call, I think? */

typedef void (AudioGenChunkFn)(int *buffer, uint32_t length);

bool audio_setup(AudioGenChunkFn *generate_chunk_);
void audio_play(void);
void audio_pause(void);

#ifdef __cplusplus
}
#endif

#endif
