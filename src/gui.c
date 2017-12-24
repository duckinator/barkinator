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

void gui_main()
{
    SynthGui *gui = gui_new();

    struct nk_color background = nk_rgb(28,48,62);

    int vertical_margin = 50;
    int horizontal_margin = 50;
    int column_height = gui->height - (vertical_margin * 2);

    int columns = 4; /* 3 synths + 1 general controls. */

    int column_spacing = 25;
    int total_width = gui->width - (column_spacing * 2) - (horizontal_margin * 2);
    int column_width = total_width / columns;
    while (poll_sdl_input(gui))
    {
        if (nk_begin(gui->ctx, "Demo1", nk_rect(50, 50, column_width, column_height),
                    NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(gui->ctx, 30, 80, 1);
            if (nk_button_label(gui->ctx, "button"))
                printf("button pressed!\n");
            nk_layout_row_dynamic(gui->ctx, 30, 2);
            if (nk_option_label(gui->ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(gui->ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(gui->ctx, 22, 1);
            nk_property_int(gui->ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(gui->ctx);

        gui_draw(gui->win, background);
    }

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(gui->glContext);
    SDL_DestroyWindow(gui->win);
    SDL_Quit();
}
