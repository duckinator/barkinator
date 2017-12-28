#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <stdbool.h>

typedef struct synthesizer_s {
    uint8_t (*oscillator)();
    size_t frequency;
    int a;
    int b;
    int c;
    bool enabled;
} Synth;


bool synth_setup(int argc, char *argv[]);
Synth *synth_new(uint8_t (*oscillator)(), size_t frequency, int a, int b, int c);
void synth_update(Synth *synth, uint8_t (*oscillator)(), size_t frequency, int a, int b, int c);

#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )


#endif
