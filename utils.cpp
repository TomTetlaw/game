#include "includes.h"

float current_time = 0.0f;
float delta_time = 0.0f;
Vec2 cursor_position;

void quit() {
    font_shutdown();
    ent_shutdown();
    hotload_shutdown();
    r_shutdown();
    tex_shutdown();
    SDL_Quit();
    
    exit(0);
}

void fatal_error(const char *title, const char *text, ...) {
    va_list args;
    char buffer[1024] = {0};
    
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);
    
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, buffer, null);
    quit();
}

Load_File_Result load_entire_file(const char *filename) {
	FILE *f = null;
	Load_File_Result result;
    
	fopen_s(&f, filename, "rb");
    defer { fclose(f); };
    
	if (!f) {
        assert(false, "failed to load file %s", filename);
		return result;
	}
    
	int len = 0;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
    
	unsigned char *buffer = allocn(unsigned char, len + 1);
	fread_s((void*)buffer, len + 1, len, 1, f);
	buffer[len] = 0;
    
	result.data = buffer;
	result.length = len;
	return result;
}

bool point_box_intersection(Vec2 point, Vec2 boxp, Vec2 boxs, bool box_centered) {
    if(box_centered) {
        float halfw = boxs.x / 2;
        float halfh = boxs.y / 2;
        if(point.x < boxp.x - halfw) return false;
        if(point.y < boxp.y - halfh) return false;
        if(point.x > boxp.x + halfw) return false;
        if(point.y > boxp.y + halfh) return false;
    } else {
        if(point.x < boxp.x) return false;
        if(point.y < boxp.y) return false;
        if(point.x > boxp.x + boxs.x) return false;
        if(point.y > boxp.y + boxs.y) return false;
    }
    
    return true;
}