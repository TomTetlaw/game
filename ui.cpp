#include "includes.h"

struct UI_Context {
    int id = -1;
    Vec2 origin;
    Vec2 bounds;
    Vec2 offset;
};

internal Array<UI_Context> contexts;
internal int current_context = -1;
bool ui_wants_mouse_input = false;
bool ui_wants_keyboard_input = false;

struct UI_Label {
    int context = -1;
    Vec2 position;
    char text[1024] = {0};
    Vec4 colour = Vec4(1,1,1,1);
};

struct UI_Box {
    int context = -1;
    Vec2 position;
    Vec2 size;
    Vec4 colour = Vec4(127/255.0f, 122/255.0f, 255/255.0f, 0.2f);
};

internal Array<UI_Label> labels;
internal Array<UI_Box> boxes;

struct UI_Click {
    Vec2 position;
    bool down = false;
};

internal Array<UI_Click> clicks;

void ui_begin_frame() {
    ui_wants_mouse_input = false;
    ui_wants_keyboard_input = false;
}

void ui_end_frame() {
    for(int i = 0; i < contexts.count; i++) {
        UI_Context *context = &contexts[i];
        if(point_box_intersection(cursor_position, contexts[i].origin, context[i].bounds)) ui_wants_mouse_input = true;
    }
        
    for(int i = 0; i < boxes.count; i++) {
        UI_Context *context = &contexts[boxes[i].context];
        r_render_box(boxes[i].position, Vec2(context->bounds.x, boxes[i].size.y), boxes[i].colour);
    }
    for(int i = 0; i < labels.count; i++) {
        r_render_string(labels[i].position, labels[i].text, labels[i].colour);
    }
    
    clicks.count = 0;
    labels.count = 0;
    boxes.count = 0;
}

void ui_process_event(SDL_Event *event) {
    if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        UI_Click click;
        click.position = cursor_position;
        click.down = event->type == SDL_MOUSEBUTTONDOWN;
        array_add(&clicks, click);
    }    
}

void ui_begin(Vec2 origin) {
    UI_Context context;
    context.id = contexts.count;
    context.origin = origin;
    current_context = context.id;
    array_add(&contexts, context);
}

void ui_end() {
    if(current_context < 0) return;
    UI_Context *context = &contexts[current_context];
    
    UI_Box box = {context->id, context->origin, context->bounds};
    array_add(&boxes, box);
    
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

void ui_update_for_new_item(UI_Context *context, Vec2 size) {
    context->offset.y += size.y;
    context->bounds.y += size.y;
    context->bounds.x = max(context->bounds.x, size.x);
}

void ui_label(const char *text) {
    if(current_context < 0) return;
    UI_Context *context = &contexts[current_context];
    
    Vec2 string_size = get_string_size(null, text);
    
    UI_Label label;
    label.context = context->id;
    label.position = context->origin + context->offset;
    strcpy(label.text, text);
    array_add(&labels, label);
    
    ui_update_for_new_item(context, string_size);
}

bool ui_button(const char *text) {
    if(current_context < 0) return false;
    UI_Context *context = &contexts[current_context];
    
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
    
    UI_Box box = {context->id, context->origin + context->offset, string_size, colour};
    array_add(&boxes, box);
    
    UI_Label label;
    label.context = context->id;
    label.position = context->origin + context->offset;
    strcpy(label.text, text);
    label.colour = Vec4(1,1,1,1);
    array_add(&labels, label);
    
    ui_update_for_new_item(context, string_size);
    
    return pressed;
}

void ui_spacing() {
    if(current_context < 0) return;
    UI_Context *context = &contexts[current_context];
    ui_update_for_new_item(context, Vec2(0, 16));
}