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
    
    Texture *test = load_texture("data/textures/test.jpg");
    
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
        switch(event.type) {
        case SDL_QUIT:
            quit();
            break;
        }
        
        r_begin_frame();
        r_render_string(Vec2(100, 100), "Hello, world! This is a message that is not rendering correctly, but when it does this will be wrong, go figure");
        r_render_texture(load_font("data/fonts/consolas.ttf", 16)->texture, Vec2(300, 300));
        r_render_texture(test, Vec2(500,500));
        r_end_frame();        
    }
        
    return 0;
}