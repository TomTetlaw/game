#ifndef UI_H
#define UI_H

extern bool ui_wants_mouse_input;
extern bool ui_wants_keyboard_input;

void ui_begin_frame();
void ui_end_frame();
void ui_render();
void ui_process_event(SDL_Event *event);

void ui_begin(int id, Vec2 origin);
void ui_end(int id);

void ui_label(const char *text);
void ui_label_format(const char *text, ...);
bool ui_button(const char *label);

void ui_spacing();

bool ui_begin_context_label(int id, const char *text);
void ui_end_context_label(int id);

int ui_get_new_context();

#endif
