#ifndef COMMON_H
#define COMMON_H

#include <error.h>
#include <stdbool.h>

#define SAMPLE_RATE 96000 /* Sample rate we want the device to accept. */
#define CHANNELS    2     /* 1 = mono, 2 = stereo. */
#define SAMPLES     2048  /* Samples per function call, I think? */



#define FAIL(...) error(1, 0, __VA_ARGS__);

#define foreach(fn, ary, ...)                                       \
    for (size_t __fe_idx = 0; ary[__fe_idx] != NULL; __fe_idx++) {  \
        fn(ary[__fe_idx], ##__VA_ARGS__);                           \
    }

static bool keep_running = true;

#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )

#endif
