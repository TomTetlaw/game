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
    
    Load_File_Result result = load_entire_file(filename);
    if(!result.data) return null;
    
    font_info = alloc(Font);
    
    unsigned char *bitmap = allocn(unsigned char, 512*512);
    stbtt_BakeFontBitmap(result.data, 0, point_size, bitmap, 512, 512, 32, 96, font_info->glyphs);    
    font_info->texture = create_bitmap(filename, bitmap, 512, 512);
    free(bitmap);
    
    font_info->point_size = point_size;
    font_info->filename = filename;
    array_add(&fonts, font_info);
    
    return font_info;
}