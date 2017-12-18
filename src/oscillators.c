#include "oscillators.h"
#include "common.h"

// TODO: Verify this actually generates a sawtooth wave.
uint8_t sawtooth(size_t frequency, uint32_t idx) {
    size_t period_samples = SAMPLE_RATE / frequency;
    return (idx % period_samples) / 2;
}

uint8_t square(size_t frequency, uint32_t idx) {
    size_t period_samples = SAMPLE_RATE / frequency;
    size_t half_period_samples = period_samples / 2;

    if ((idx % period_samples) > half_period_samples) {
        return 255;
    } else {
        return 0;
    }
}
