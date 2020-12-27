#ifndef UI_H
#define UI_H

void ui_render();
bool ui_process_event(SDL_Event *event);

void ui_begin(Vec2 origin);
void ui_end();

void ui_label(const char *text);
void ui_label_format(const char *text, ...);

#endif
