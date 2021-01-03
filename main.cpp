#include "includes.h"

struct My_Entity { // @entity_type
    entity_stuff(My_Entity);
};

struct My_Entity1 { // @entity_type
    entity_stuff(My_Entity1);
};

struct My_Entity2 { // @entity_type
    entity_stuff(My_Entity2);
};

struct My_Entity3 { // @entity_type
    entity_stuff(My_Entity3);
};

struct My_Entity4 { // @entity_type
    entity_stuff(My_Entity4);
};

struct My_Entity5 { // @entity_type
    entity_stuff(My_Entity5);
};

struct My_Entity6 { // @entity_type
    entity_stuff(My_Entity6);
};

struct My_Entity7 { // @entity_type
    entity_stuff(My_Entity7);
};

struct My_Entity8 { // @entity_type
    entity_stuff(My_Entity8);
};

struct My_Entity9 { // @entity_type
    entity_stuff(My_Entity9);
};

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
    
    bool left_pressed = false;
    bool right_pressed = false;
    Vec2 context_position;
    Entity *selected_entity = null;
    
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
        
        left_pressed = false;
        right_pressed = false;
        
        while(SDL_PollEvent(&event)) {
            ui_process_event(&event);
            if(ui_wants_mouse_input || ui_wants_keyboard_input) continue;
            
            switch(event.type) {
            case SDL_QUIT:
                quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_RIGHT) right_pressed = true;
                if(event.button.button == SDL_BUTTON_LEFT) left_pressed = true;
                break;
            }
        }
        
        ui_begin_frame();
        
        static bool context_menu_open = false;
        if(right_pressed) {
            context_menu_open = true;
            context_position = cursor_position;
            
            for(int i = 0; i < entities.size; i++) {
                if(!entities.filled[i]) continue;
                if(entities[i].remove_me) continue;
                Entity *entity = &entities[i];
                
                if(point_box_intersection(cursor_position, entity->position, Vec2(entity->texture->width, entity->texture->height), true)) {
                    selected_entity = entity;
                    break;
                }
            }
        }
        
        if(context_menu_open) {
            ui_begin(context_position);
            
            if(selected_entity) {
                if(ui_button("Remove")) ent_remove_base(selected_entity);
            } else {
                if(ui_begin_context_label("Create Entity >")) {
                    for(int i = 0; i < num_entity_types; i++) {
                        if(ui_button(entity_type_names[i])) {
                            Entity *ent = ent_create_from_name(entity_type_names[i]);
                            ent->position = cursor_position;
                            ent->texture = load_texture("data/textures/test.jpg");
                        }
                    }
                }
                ui_end_context_label();
            }
            
            ui_end();
        }
        
        if(left_pressed) {
            context_menu_open = false;
            selected_entity = null;
        }
        
        ui_end_frame();
        
        ent_update();
        ent_render();
        
        r_render_frame();
    }
        
    return 0;
}