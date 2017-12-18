#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

typedef struct synthesizer_s {
    uint8_t (*oscillator)();
    size_t frequency;
    int a;
    int b;
    int c;
} Synth;

Synth *new_synth(uint8_t (*oscillator)(), size_t frequency, int a, int b, int c);

#endif
