#include <SDL.h>
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

bool setup(void (*callback)())
{
    // Initialize audio device.
    return audio_setup(callback);
}

int main(int argc, char *argv[])
{
    if (!setup(generate_chunk)) {
        return 1;
    }

    // Busy loop until we want to exit.
    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
