#ifndef OSCILLATORS_H
#define OSCILLATORS_H

#include <stddef.h>
#include <stdint.h>

uint8_t sawtooth(size_t frequency, uint32_t idx);
uint8_t square(size_t frequency, uint32_t idx);
int one();
int two();
int three();
int four();

#endif
