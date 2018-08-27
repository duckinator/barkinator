#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

uint8_t sawtooth(size_t frequency, uint32_t idx);
uint8_t square(size_t frequency, uint32_t idx);

typedef uint8_t Oscillator(size_t, uint32_t);

static Oscillator *oscillators[] = {
    *sawtooth,
    *square,
};

enum {SAWTOOTH, SQUARE};

#ifdef __cplusplus
}
#endif

#endif
