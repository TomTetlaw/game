#include "includes.h"

Array<Font *> fonts;

void font_shutdown() {
	for (int i = 0; i < fonts.count; i++) free(fonts[i]);
}

Font *load_font(const char *filename, int point_size) {
	Font *font_info = nullptr;
    
	for (int i = 0; i < fonts.count; i++) {
		font_info = fonts[i];
		if (!strcmp(font_info->filename, filename) && font_info->point_size == point_size) {
			return font_info;
		}
	}
    
    return null;
}