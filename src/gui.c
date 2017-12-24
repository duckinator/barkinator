#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION
#include "../nuklear/nuklear.h"
#include "../nuklear/demo/sdl_opengl3/nuklear_sdl_gl3.h" // SHRUG. WHATEVER.


#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#include "synth/oscillators.h"
#include "synth/audio.h"

#include "synth/synth.h"
extern Synth *synths[];

typedef struct synth_gui_s {
    SDL_Window *win;
    SDL_GLContext glContext;
    struct nk_context *ctx;
    int height;
    int width;
} SynthGui;

SynthGui *gui_new()
{
    SynthGui *gui = malloc(sizeof(SynthGui));
    memset(gui, 0, sizeof(SynthGui));

    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    gui->win = SDL_CreateWindow("Demo",
            0, 0, 640, 480,
            SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_FULLSCREEN_DESKTOP);
    gui->glContext = SDL_GL_CreateContext(gui->win);

    SDL_GetWindowSize(gui->win, &(gui->width), &(gui->height));

    /* OpenGL setup */
    glViewport(0, 0, gui->width, gui->height);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    gui->ctx = nk_sdl_init(gui->win);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();

    return gui;
}

void gui_draw(SDL_Window *win, struct nk_color background)
{
    float bg[4];
    int win_width;
    int win_height;

    nk_color_fv(bg, background);

    SDL_GetWindowSize(win, &win_width, &win_height);

    glViewport(0, 0, win_width, win_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);

    /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI. */
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(win);
}

bool poll_sdl_input(SynthGui *gui)
{
    SDL_Event evt;
    nk_input_begin(gui->ctx);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            return false;
        }
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(gui->ctx);

    return true;
}

typedef struct synth_gui_synth_position_s {
    size_t top;
    size_t left;
    size_t width;
    size_t height;
} SynthPosition;

SynthPosition *gui_calculate_synth_position(SynthGui *gui,
        size_t rows, size_t columns, size_t synth_index)
{
    size_t vertical_margin = 50;
    size_t horizontal_margin = 50;

    size_t row_spacing = 25;
    size_t total_height = gui->height - (row_spacing * (rows - 1)) - (vertical_margin * 2);
    size_t row_height = total_height / rows;

    size_t column_spacing = 25;
    size_t total_width = gui->width - (column_spacing * (columns - 1)) - (horizontal_margin * 2);
    size_t column_width = total_width / columns;

    size_t synth_number = synth_index + 1;

    SynthPosition *pos = malloc(sizeof(SynthPosition));
    memset(pos, 0, sizeof(SynthPosition));


    pos->top    = vertical_margin;
    pos->left   = horizontal_margin + (column_spacing * (synth_index)) + (column_width * (synth_index));
    pos->width  = column_width;
    pos->height = row_height;

    return pos;
}


void gui_add_synth(SynthGui *gui, size_t rows, size_t columns, size_t synth_index)
{
    Synth *synth = synths[synth_index];

    SynthPosition *pos = gui_calculate_synth_position(gui, rows, columns, synth_index);

    size_t pretty_synth_index = synth_index + 1;
    size_t label_length = strlen("Synth ") + (pretty_synth_index / 10) + 2;
    char *column_label = malloc(label_length);

    memset(column_label, 0, label_length);
    snprintf(column_label, label_length, "Synth %u", pretty_synth_index);

    if (nk_begin(gui->ctx, column_label, nk_rect(pos->left, pos->top, pos->width, pos->height),
                NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nk_layout_row_static(gui->ctx, 30, 80, 1);
        if (nk_button_label(gui->ctx, "button")) {
            audio_play();
            synth->enabled = !(synth->enabled);
        }

        nk_layout_row_dynamic(gui->ctx, 30, 2);
        if (nk_option_label(gui->ctx, "sawtooth", synth->oscillator == oscillators[SAWTOOTH])) {
            synth->oscillator = oscillators[SAWTOOTH];
        }
        if (nk_option_label(gui->ctx, "square",   synth->oscillator == oscillators[SQUARE])) {
            synth->oscillator = oscillators[SQUARE];
        }

        nk_layout_row_dynamic(gui->ctx, 22, 1);
        nk_property_int(gui->ctx, "A", 0, &(synth->a), 100, 10, 1);

        nk_layout_row_dynamic(gui->ctx, 22, 1);
        nk_property_int(gui->ctx, "B", 0, &(synth->b), 100, 10, 1);

        nk_layout_row_dynamic(gui->ctx, 22, 1);
        nk_property_int(gui->ctx, "C", 0, &(synth->c), 100, 10, 1);
    }
    nk_end(gui->ctx);
}

void gui_main()
{
    SynthGui *gui = gui_new();

    struct nk_color background = nk_rgb(28,48,62);

    int rows = 2; /* synth settings + main controls. */
    int number_of_synths = 2;

    int columns = number_of_synths;


    while (poll_sdl_input(gui))
    {
        for (uint8_t i = 0; i < number_of_synths; i++) {
            gui_add_synth(gui, rows, columns, i);
        }

        gui_draw(gui->win, background);
    }

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(gui->glContext);
    SDL_DestroyWindow(gui->win);
    SDL_Quit();
}
