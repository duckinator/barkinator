#include <SDL.h>
#include "synth/common.h"

int main(int argc, char *argv[])
{
    if (!setup(argc, argv)) {
        return 1;
    }

    // Busy loop until we want to exit.
    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }

    return 0;
}
