#include "includes.h"

struct UI_Label {
    Vec2 position;
    Vec2 size;
    char text[1024] = {0};
    Vec4 colour = Vec4(1,1,1,1);
    bool hovering = false;
};

struct UI_Box {
    Vec2 position;
    Vec2 size;
    Vec4 colour = Vec4(127/255.0f, 122/255.0f, 255/255.0f, 0.2f);
};

struct UI_Context {
    int id = -1;
    Vec2 origin;
    Vec2 bounds;
    Vec2 offset;
    Array<UI_Label> labels;
    Array<UI_Box> boxes;
    int currently_hovering = -1;
};

internal Array<UI_Context> contexts;
internal int current_context = -1;
bool ui_wants_mouse_input = false;
bool ui_wants_keyboard_input = false;

struct UI_Click {
    Vec2 position;
    bool down = false;
};

internal Array<UI_Click> clicks;

int next_context = 0;
int ui_get_new_context() { return next_context++; }

UI_Context *get_context(int id) {
    if(id < 0) return null;
    
    if(contexts.count <= id) {
        UI_Context context;
        array_add(&contexts, context);
        return &contexts[contexts.count-1];
    }
    
    return &contexts[id];
}

void ui_begin_frame() {
    ui_wants_mouse_input = false;
    ui_wants_keyboard_input = false;
}

void ui_end_frame() {
    for(int i = 0; i < contexts.count; i++) {
        UI_Context *context = &contexts[i];
        if(point_box_intersection(cursor_position, contexts[i].origin, context[i].bounds)) ui_wants_mouse_input = true;
        
        for(int i = 0; i < context->boxes.count; i++) {
            r_render_box(context->boxes[i].position, Vec2(context->bounds.x, context->boxes[i].size.y), context->boxes[i].colour);
        }
        for(int i = 0; i < context->labels.count; i++) {
            r_render_string(context->labels[i].position, context->labels[i].text, context->labels[i].colour);
        }
        
        context->labels.count = 0;
        context->boxes.count = 0;
    }
    
    clicks.count = 0;
    contexts.count = 0;
}

void ui_process_event(SDL_Event *event) {
    if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        if(event->button.button != SDL_BUTTON_LEFT) return;
        
        UI_Click click;
        click.position = cursor_position;
        click.down = event->type == SDL_MOUSEBUTTONDOWN;
        array_add(&clicks, click);
    }    
}

void ui_begin(int id, Vec2 origin) {
    UI_Context *context = get_context(id);
    context->id = contexts.count;
    context->origin = origin;
    current_context = id;
}

void ui_end(int id) {
    UI_Context *context = get_context(id);
    if(!context) return;
    
    UI_Box box = {context->origin, context->bounds};
    array_add(&context->boxes, box);    
    
    current_context = -1;
}

void ui_label_format(const char *text, ...) {
    va_list args;
    char buffer[1024] = {0};
    
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    
    ui_label(buffer);
}

void ui_update_for_new_item(UI_Context *context, Vec2 size) {
    context->offset.y += size.y;
    context->bounds.y += size.y;
    context->bounds.x = max(context->bounds.x, size.x);
}

void ui_label(const char *text) {
    UI_Context *context = get_context(current_context);
    if(!context) return;
    
    Vec2 string_size = get_string_size(null, text);
    
    UI_Label label;
    label.position = context->origin + context->offset;
    label.size = string_size;
    strcpy(label.text, text);
    array_add(&context->labels, label);
    
    ui_update_for_new_item(context, string_size);
}

bool ui_button(const char *text) {
    UI_Context *context = get_context(current_context);
    if(!context) return;
    
    Vec2 string_size = get_string_size(null, text);
    Vec4 colour = Vec4(127/255.0f, 122/255.0f, 255/255.0f, 0.2f);
    bool pressed = false;
    if(point_box_intersection(cursor_position, context->origin+context->offset, string_size)) {
        colour = Vec4(127/255.0f, 122/255.0f, 255/255.0f, 0.5f);
        for(int i = 0; i < clicks.count; i++) {
            if(clicks[i].down && point_box_intersection(clicks[i].position, context->origin+context->offset, string_size)) {
                pressed = true;
            }
        }
    }
    
    UI_Box box = {context->origin + context->offset, string_size, colour};
    array_add(&context->boxes, box);
    
    UI_Label label;
    label.position = context->origin + context->offset;
    strcpy(label.text, text);
    label.colour = Vec4(1,1,1,1);
    array_add(&context->labels, label);
    
    ui_update_for_new_item(context, string_size);
    
    return pressed;
}

void ui_spacing() {
    UI_Context *context = get_context(current_context);
    if(!context) return;
    ui_update_for_new_item(context, Vec2(0, 16));
}

bool ui_begin_context_label(int id, const char *text) {
    UI_Context *context = get_context(current_context);
    if(!context) return;
    
    ui_label(text);
    UI_Label *label = &context->labels[context->labels.count - 1];
    bool hovering = point_box_intersection(cursor_position, label->position, label->size);
    if(hovering) context->currently_hovering = context->labels.count - 1;
    
    bool should_show = context->currently_hovering == (context->labels.count - 1);
    
    float xpos = label->position.x + label->size.x;
    float ypos = label->position.y;
    ui_begin(Vec2(xpos, ypos));
    
    return should_show;
}

void ui_end_context_label(int id) {
    ui_end(int id);
}
    
    
    
    
    
    
    