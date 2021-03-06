#include <SDL.h>
#include "synth/synth.h"

extern void gui_main();

int main(int argc, char *argv[])
{
    if (!synth_setup(argc, argv)) {
        return 1;
    }

    gui_main();

    // Busy loop until we want to exit.
/*    while (keep_running) {
        SDL_Delay(100); // Sleep 1/10th of a second.
    }*/

    return 0;
}
