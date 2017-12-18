#include <SDL.h>
#include "oscillators.h"
#include "audio.h"
#include "common.h"

typedef struct synthesizer_s {
    uint8_t (*oscillator)();
    size_t frequency;
    int a;
    int b;
    int c;
} Synth;

Synth *synths[] = {
    NULL,
    NULL,
    NULL,
};

long i = 0;

Synth *new_synth(uint8_t (*oscillator)(), size_t frequency, int a, int b, int c)
{
    Synth *synth = malloc(sizeof(Synth));
    memset(synth, 0, sizeof(Synth));

    synth->oscillator   = oscillator;
    synth->frequency    = frequency;
    synth->a            = a;
    synth->b            = b;
    synth->c            = c;

    return synth;
}

void run_synth(Synth *synth, int *buffer, uint32_t length, uint32_t buffer_idx) {
    long int idx = (i >> synth->a | i >> synth->b) & (i >> synth->c);

    buffer[buffer_idx] = louder(synth->oscillator(synth->frequency, idx));
    i++;
}

void generate_chunk(int *buffer, uint32_t length)
{
    for (uint32_t idx = 0; idx < length;) {
        foreach(run_synth, synths, buffer, length, idx++);
    }
}

bool setup(void (*callback)())
{
    // Initialize audio device.
    return audio_setup(callback);
}

int main(int argc, char *argv[])
{
    synths[0] = new_synth(sawtooth, 30, 12, 3,  4);
    synths[1] = new_synth(square,   60, 10, 3, -2);

    if (!setup(generate_chunk)) {
        return 1;
    }

    // Busy loop until we want to exit.
    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
