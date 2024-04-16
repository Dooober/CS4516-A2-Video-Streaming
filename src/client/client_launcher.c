#include <stdio.h>
#include <stdlib.h>

#include "client.h"

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
#define NK_SDL_GL2_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl2.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/*
    Using SDL to create a window, following the sdl_opengl2 demo in Nuklear
*/
SDL_Window* create_window() {
    SDL_Window *window;

    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    window = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);

    return window;
}

/*
	def createWidgets(self):
		"""Build GUI."""
		# Create Setup button
		self.setup = Button(self.master, width=20, padx=3, pady=3)
		self.setup["text"] = "Setup"
		self.setup["command"] = self.setupMovie
		self.setup.grid(row=1, column=0, padx=2, pady=2)
		
		# Create Play button		
		self.start = Button(self.master, width=20, padx=3, pady=3)
		self.start["text"] = "Play"
		self.start["command"] = self.playMovie
		self.start.grid(row=1, column=1, padx=2, pady=2)
		
		# Create Pause button			
		self.pause = Button(self.master, width=20, padx=3, pady=3)
		self.pause["text"] = "Pause"
		self.pause["command"] = self.pauseMovie
		self.pause.grid(row=1, column=2, padx=2, pady=2)
		
		# Create Teardown button
		self.teardown = Button(self.master, width=20, padx=3, pady=3)
		self.teardown["text"] = "Teardown"
		self.teardown["command"] =  self.exitClient
		self.teardown.grid(row=1, column=3, padx=2, pady=2)
		
		# Create a label to display the movie
		self.label = Label(self.master, height=19)
		self.label.grid(row=0, column=0, columnspan=4, sticky=W+E+N+S, padx=5, pady=5) 
*/
void create_widgets(struct nk_context* ctx, struct client* client) {
	nk_layout_row_static(ctx, 30, 80, 4);
	if (nk_button_label(ctx, "Setup"))
		setup_movie(client);
	if (nk_button_label(ctx, "Play"))
		play_movie(client);
	if (nk_button_label(ctx, "Pause"))
		pause_movie(client);
	if (nk_button_label(ctx, "Teardown"))
		exit_client(client);

    nk_layout_row_static(ctx, 540, 960, 1);
}


/*
    The main GUI loop
*/
void run(struct client* client, struct nk_context* ctx, SDL_Window* window) {
    int running = 1;
    int win_width, win_height;
    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

    SDL_GetWindowSize(window, &win_width, &win_height);

    while (running)
    {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) running = 0;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        /* GUI */ 
        if (nk_begin(ctx, "Demo", nk_rect(0, 0, win_width, win_height),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            create_widgets(ctx, client);
        }
        nk_end(ctx);
        

        /* Draw */
        SDL_GetWindowSize(window, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_GL_SwapWindow(window);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: client [Server Name] [Server Port] [RTP Port] [Video File]\n");
        return -1;
    }

    char* server_addr = argv[1];
    int server_port = atoi(argv[2]);
    int rtp_port = atoi(argv[3]);
    char* filename = argv[4];

    // Startup 

    SDL_Window *window = create_window();
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    struct nk_context* ctx = nk_sdl_init(window);
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();

    // Create client and run app

    struct client client = create_client(server_addr, server_port, rtp_port, filename);

    run(&client, ctx, window);

    // Shutdown

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}