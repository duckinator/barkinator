#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <stdbool.h>

typedef struct synthesizer_s {
    uint8_t (*oscillator)();
    size_t frequency;
    int a;
    int b;
    int c;
} Synth;


bool synth_setup(int argc, char *argv[]);
Synth *synth_new(uint8_t (*oscillator)(), size_t frequency, int a, int b, int c);
void synth_update(Synth *synth, uint8_t (*oscillator)(), size_t frequency, int a, int b, int c);

#define foreach(fn, ary, ...)                                       \
    for (size_t __fe_idx = 0; ary[__fe_idx] != NULL; __fe_idx++) {  \
        fn(ary[__fe_idx], ##__VA_ARGS__);                           \
    }

#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )


#endif
