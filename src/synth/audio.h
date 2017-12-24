#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>

bool audio_setup(void (*generate_chunk)());
void audio_play();
void audio_pause();

#endif
