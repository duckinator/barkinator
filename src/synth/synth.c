#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // for malloc()
#include <string.h> // for memset()

#include <SDL.h>
#include "oscillators.h"
#include "audio.h"
#include "synth.h"

// These are the actual synthesizers! The number is hard-coded, atm.
Synth *synths[] = {
    NULL,
    NULL,
    NULL,
};

// Magical variable used to generate audio.
long i = 0;

Synth *synth_new(uint8_t (*oscillator)(), size_t frequency, int a, int b, int c)
{
    Synth *synth = malloc(sizeof(Synth));
    memset(synth, 0, sizeof(Synth));

    synth_update(synth, oscillator, frequency, a, b, c);

    return synth;
}

void synth_update(Synth *synth, uint8_t (*oscillator)(), size_t frequency, int a, int b, int c)
{
    synth->oscillator   = oscillator;
    synth->frequency    = frequency;
    synth->a            = a;
    synth->b            = b;
    synth->c            = c;
}

void run_synth(Synth *synth, int *buffer, uint32_t length, uint32_t buffer_idx) {
    long int cof = (synth->c < 0) ? (i << -(synth->c)) : (i >> synth->c);
    long int idx = (i >> synth->a | i >> synth->b) & cof;

    buffer[buffer_idx] = louder(synth->oscillator(synth->frequency, idx)) - 50;
    i++;
}

void generate_chunk(int *buffer, uint32_t length)
{
    for (uint32_t idx = 0; idx < length;) {
        foreach(run_synth, synths, buffer, length, idx++);
    }
}

bool synth_setup(int argc, char *argv[])
{
    synths[0] = synth_new(sawtooth, 30, 12, 3,  4);
    synths[1] = synth_new(square,   60, 10, 3, -2);

    if (!audio_setup(generate_chunk)) {
        return false;
    }


    return true;
}
