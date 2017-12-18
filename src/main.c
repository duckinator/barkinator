#include <SDL.h>
#include "oscillators.h"
#include "audio.h"
#include "common.h"

int (*sounds[])() = {
    one,
    two,
    //    three,
    //    four,
    NULL,
};

long i = 0;

void run_oscillator(int (*fn)(), int *buffer, uint32_t length, uint32_t idx) {
    buffer[idx] = fn(i);
    i++;
}

void generate_chunk(int *buffer, uint32_t length)
{
    for (uint32_t idx = 0; idx < length;) {
        foreach(run_oscillator, sounds, buffer, length, idx++);
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
