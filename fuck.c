#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <error.h>

#define FAIL(...) error(1, 0, __VA_ARGS__);

SDL_AudioSpec wanted;
bool keep_running = true;

void cleanup()
{
    keep_running = false;
    SDL_CloseAudio();
}


#define quieter(x) ( ((x) & 0xFF) >> 2)
#define louder(x)  (  (x) << 2 )

long i = 0;

int one() {
    return louder(i * (i >> 12 | i >> 3) & 30 & (i >> 4));
}

int two() {
  return (i * (i >> 50 | i >> 3));
}

#define foreach(fn, ary, n, ...)                            \
    for (size_t __fe_idx = 0; __fe_idx < n; __fe_idx++) {   \
        fn(ary[__fe_idx], ##__VA_ARGS__);         \
    }

#define NUM_OSCILLATORS 2
int (*sounds[NUM_OSCILLATORS])() = {
    one,
    two,
};

void run_oscillator(int (*fn)(), int *ibuffer, uint32_t ilength, uint32_t idx) {
    ibuffer[idx] = fn();
    i++;
}

void generate_chunk(uint8_t *buffer, uint32_t length)
{
    memset(buffer, 0, length);
    int *ibuffer = (int*)buffer;
    uint32_t ilength = (length * sizeof(uint8_t)) / sizeof(int);

    for (uint32_t idx = 0; idx < ilength;) {
        foreach(run_oscillator, sounds, NUM_OSCILLATORS, ibuffer, ilength, idx++);
    }
}

/*
 * Generate audio and shove it into the output stream.
 *
 * +udata+:  Fuck if I even know what this is for.
 * +stream+: Pointer to the audio buffer to be filled.
 * +length+: The length (in bytes) of the audio buffer.
 */
void fill_audio(void *udata, uint8_t *stream, int length)
{
    if (length < 0) {
        FAIL("fill_audio: ??? length < 0");
        return;
    }

    uint32_t ulength = (uint32_t)length;
    uint8_t *buffer = malloc(ulength);

    if (buffer == NULL) {
        FAIL("buffer is NULL");
    }

    generate_chunk(buffer, ulength);

    SDL_MixAudio(stream, buffer, ulength, SDL_MIX_MAXVOLUME / 2);

    // Why the fuck does this cause a memory access error?!
    //free(original_buffer);
    SDL_Delay(10);
}

// Acquire access to an audio device.
void open_audio_device()
{
    // Specify wanted audio format.
    wanted.freq = 96000;    // Sample rate. I think?
    wanted.format = AUDIO_U8;
    wanted.channels = 2;    // 1 = mono, 2 = stereo.
    wanted.samples = 2048;  // Samples per function call. I think?
    wanted.callback = fill_audio;
    wanted.userdata = NULL;

    // Open the audio device, forcing the desired format.
    if (SDL_OpenAudio(&wanted, NULL) < 0) {
        FAIL("Couldn't open audio device: %s", SDL_GetError());
    }
}

int main(int argc, char *argv[])
{
    // Always run cleanup() before exiting.
    atexit(cleanup);

    // Initialize audio device.
    open_audio_device();

    // Play audio.
    SDL_PauseAudio(0);

    // Busy loop until we want to exit.
    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
