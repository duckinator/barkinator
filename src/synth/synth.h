#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#ifdef __cplusplus
extern "C" {
#endif

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

typedef void (SynthCreationCallback)(Synth *synth);

// FIXME: Is there a less gross way to do this?
static SynthCreationCallback *synth_register =
#ifdef __cplusplus
    nullptr;
#else
    NULL;
#endif

bool synth_setup(int argc, char *argv[]);
Synth *synth_new(SynthOscillatorFn *oscillator, size_t frequency,
                 int a, int b, int c);
void synth_update(Synth *synth, SynthOscillatorFn *oscillator,
                  size_t frequency, int a, int b, int c);
void synth_register_callback(SynthCreationCallback *fn);

#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )

#ifdef __cplusplus
}
#endif

#endif
