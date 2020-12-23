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
    defer { free(result.data); };
    
    font_info = alloc(Font);
    
    int bitmap_width = 512;
    int bitmap_height = 100;
    unsigned char *bitmap = allocn(unsigned char, bitmap_width * bitmap_height);
    defer { free(bitmap); };
    
    stbtt_pack_context spc;
    stbtt_PackBegin(&spc, bitmap, bitmap_width, bitmap_height, bitmap_width, 1, null);
    stbtt_PackFontRange(&spc, result.data, 0, point_size/2, 32, 96, font_info->glyphs);
    stbtt_PackEnd(&spc);
    
    font_info->texture = create_bitmap(font_info->filename, bitmap, bitmap_width, bitmap_height);
    
    font_info->point_size = point_size;
    font_info->filename = filename;
    array_add(&fonts, font_info);
    
    return font_info;
}