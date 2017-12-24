#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // for malloc()
#include <string.h> // for memset()
#include "synth.h"

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

