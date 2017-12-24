#include <SDL.h>
#include <error.h>
#include "audio.h"

#define FAIL(...) error(1, 0, __VA_ARGS__);

void (*audio_generate_chunk)();
SDL_AudioSpec wanted;

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

    memset(buffer, 0, length);
    int *ibuffer = (int*)buffer;
    uint32_t ilength = (length * sizeof(uint8_t)) / sizeof(int);

    audio_generate_chunk(ibuffer, ilength);

    SDL_MixAudio(stream, buffer, ulength, SDL_MIX_MAXVOLUME / 2);

    // Why the fuck does this cause a memory access error?!
    //free(original_buffer);
    SDL_Delay(10);
}

// Acquire access to an audio device.
bool open_audio_device()
{
    // Specify wanted audio format.
    // See configuration section at the top for details.
    wanted.freq     = SAMPLE_RATE;
    wanted.format   = AUDIO_U8;
    wanted.channels = CHANNELS;
    wanted.samples  = SAMPLES;
    wanted.callback = fill_audio;
    wanted.userdata = NULL;

    // Open the audio device, forcing the desired format.
    if (SDL_OpenAudio(&wanted, NULL) < 0) {
        FAIL("Couldn't open audio device: %s", SDL_GetError());
        return false;
    }

    return true;
}

void audio_cleanup()
{
    SDL_CloseAudio();
}

bool audio_setup(void (*generate_chunk_)())
{
    atexit(audio_cleanup);
    audio_generate_chunk = generate_chunk_;

    if (!open_audio_device()) {
        return false;
    }

    return true;
}

void audio_play()
{
    SDL_PauseAudio(0);
}

void audio_pause()
{
    SDL_PauseAudio(1);
}
