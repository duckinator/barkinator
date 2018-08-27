#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t (SynthOscillatorFn)(size_t frequency,
                                    uint32_t buffer_idx);

typedef struct synthesizer_s {
    SynthOscillatorFn *oscillator;
    size_t frequency;
    int a;
    int b;
    int c;
    bool enabled;
} Synth;


bool synth_setup(int argc, char *argv[]);
Synth *synth_new(SynthOscillatorFn *oscillator, size_t frequency,
                 int a, int b, int c);
void synth_update(Synth *synth, SynthOscillatorFn *oscillator,
                  size_t frequency, int a, int b, int c);

#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )


#endif
