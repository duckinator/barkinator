#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>

#define SAMPLE_RATE 96000 /* Sample rate we want the device to accept. */
#define CHANNELS    2     /* 1 = mono, 2 = stereo. */
#define SAMPLES     2048  /* Samples per function call, I think? */

bool audio_setup(void (*generate_chunk)());
void audio_play();
void audio_pause();

#endif
