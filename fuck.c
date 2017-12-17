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

uint32_t generate_chunk(uint32_t length)
{
    return 0;
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

    uint32_t ulength = (uint32_t)length; // FUCKING BITE ME, SDL.
    uint8_t *buffer = malloc(ulength);
    memset(buffer, 0, ulength);

    SDL_MixAudio(stream, buffer, ulength, SDL_MIX_MAXVOLUME / 2);

    free(buffer);
}

// Acquire access to an audio device.
void open_audio_device()
{
    // Specify wanted audio format.
    wanted.freq = 22050;
    wanted.format = AUDIO_U16;
    wanted.channels = 1;    // 1 = mono, 2 = stereo.
    wanted.samples = 1024;  // According to the internet: "Good low-latency value for callback."
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

    open_audio_device();

    /* Let the callback function play the audio chunk */
    SDL_PauseAudio(0);

    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
