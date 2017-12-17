#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

SDL_AudioSpec wanted;
void fill_audio(void *udata, uint8_t *stream, int length);

bool open_audio_device()
{
    /* Set the audio format */
    wanted.freq = 22050;
    wanted.format = AUDIO_U16;
    wanted.channels = 1;    /* 1 = mono, 2 = stereo */
    wanted.samples = 1024;  /* Good low-latency value for callback */
    wanted.callback = fill_audio;
    wanted.userdata = NULL;

    /* Open the audio device, forcing the desired format */
    if ( SDL_OpenAudio(&wanted, NULL) < 0 ) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

static uint8_t *audio_chunk;
static int audio_length;
static uint8_t *audio_position;

/* The audio function callback takes the following parameters:
 * stream:  A pointer to the audio buffer to be filled
 * len:     The length (in bytes) of the audio buffer
 */
void fill_audio(void *udata, uint8_t *stream, int length)
{
    /* Only play if we have data left */
    if ( audio_length == 0 )
        return;

    /* Mix as much data as possible */
    length = (audio_length < length) ? audio_length : length;
    SDL_MixAudio(stream, audio_position, length, SDL_MIX_MAXVOLUME / 2);
    audio_position += length;
    audio_length   -= length;
}

int main(int argc, char *argv[])
{
    /* Load the audio data ... */

    ;;;;;

    audio_position = audio_chunk;

    /* Let the callback function play the audio chunk */
    SDL_PauseAudio(0);

    /* Do some processing */

    ;;;;;

    /* Wait for sound to complete */
    while ( audio_length > 0 ) {
        SDL_Delay(100);         /* Sleep 1/10 second */
    }
    SDL_CloseAudio();
}
