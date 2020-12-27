#include "includes.h"

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) fatal_error("ERROR", "Could not initialize SDL2: %s", SDL_GetError());
    
    sdl_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(!sdl_window) fatal_error("ERROR", "Could not create window: %s", SDL_GetError());
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext context = SDL_GL_CreateContext(sdl_window);
    
    glewInit();
    
    r_init();
    tex_init();
    hotload_init();
    ent_init();
    
    SDL_Event event;
    bool should_quit = false;
    float prev_time = SDL_GetTicks() / 1000.0f;
    while(!should_quit) {
        hotload_check_files_non_blocking();
        
        float now = SDL_GetTicks() / 1000.0f;
        delta_time = now - prev_time;
        current_time = now;
        prev_time = current_time;
        
        int x=0, y=0; SDL_GetMouseState(&x, &y);
        cursor_position = Vec2(x, y);
        
        SDL_PollEvent(&event);
        if(!ui_process_event(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                quit();
                break;
            }
        }
        
        ui_begin(Vec2(100, 100));
        ui_label("Hello, world 1!");
        ui_label("Hello, world 2!");
        ui_label("Hello, world 3!");
        ui_label("Hello, world 4!");
        ui_label("Hello, world 5!");
        ui_label("Hello, world 6!");
        r_render_box(Vec2(100, 100), Vec2(100, 100)); // this renders as black because it uses the wrong shader, need to refactor the way that shaders are set so that each command has a pointer to the correct shader to use, in the future we should sort the commands by which shader it uses to reduce the number of calls to glUseProgram
        ui_end();
        
        r_render_frame();
    }
        
    return 0;
}