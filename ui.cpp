#include "includes.h"

struct UI_Context {
    int id = -1;
    Vec2 origin;
    Vec2 bounds;
    Vec2 offset;
    float line_height = 0.0f;
};

internal void ui_update_bounds(UI_Context *context, Vec2 new_item_bounds) {
    Vec2 bounds = new_item_bounds;
    context->bounds.x = max(context->bounds.x, new_item_bounds.x); 
    context->bounds.y = max(context->bounds.y, new_item_bounds.y);
}

internal Array<UI_Context> contexts;
internal int current_context = -1;

internal float ui_line_height = 32.0f;

bool ui_process_event(SDL_Event *event) {
    return false;
}

void ui_begin(Vec2 origin) {
    UI_Context context;
    context.id = contexts.count;
    context.line_height = ui_line_height;
    context.origin = origin;
    current_context = context.id;
    array_add(&contexts, context);
}

void ui_end() {
    if(current_context < 0) return;
    UI_Context *context = &contexts[current_context];
    
//    r_render_box(context->origin, context->bounds);
    array_remove(&contexts, current_context);
    current_context--;
}

void ui_label_format(const char *text, ...) {
    va_list args;
    char buffer[1024] = {0};
    
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    
    ui_label(buffer);
}

void ui_label(const char *text) {
    if(current_context < 0) return;
    UI_Context *context = &contexts[current_context];
    
    ui_update_bounds(context, get_string_size(null, text));
    r_render_string(context->origin + context->offset, text);
    context->offset.y += context->line_height;
}