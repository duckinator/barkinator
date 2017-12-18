#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "oscillators.h"
#include "audio.h"
#include "common.h"

#define NUM_OSCILLATORS 2
int (*sounds[NUM_OSCILLATORS])() = {
    one,
    two,
    //    three,
    //    four,
};

extern long i;

void run_oscillator(int (*fn)(), int *buffer, uint32_t length, uint32_t idx) {
    buffer[idx] = fn();
    i++;
}

void generate_chunk(int *buffer, uint32_t length)
{
    for (uint32_t idx = 0; idx < length;) {
        foreach(run_oscillator, sounds, NUM_OSCILLATORS, buffer, length, idx++);
    }
}

void cleanup()
{
    keep_running = false;
}

bool setup(void (*callback)())
{
    // Always run cleanup() before exiting.
    atexit(cleanup);

    // Initialize audio device.
    return audio_setup(callback);
}


int main(int argc, char *argv[])
{
    keep_running = setup(generate_chunk);

    // Play audio.
    SDL_PauseAudio(0);

    // Busy loop until we want to exit.
    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
