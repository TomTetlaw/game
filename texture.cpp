#include "includes.h"

internal Array<Texture *> textures;

internal void unload_texture(Texture *texture) {
    glDeleteTextures(1, &texture->id);
}

void tex_init() {
}

void tex_shutdown() {
    for(int i = 0; i < textures.count; i++) unload_texture(textures[i]);
}

void load_texture_base(const char *filename, uint *id, int *width, int *height) {
    unsigned char *pixels = stbi_load(filename, width, height, 0, STBI_rgb_alpha);
    if(pixels == null) fatal_error("ERROR", "Could not load image %s: %s", filename, stbi_failure_reason());
    
    glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void texture_hotload_callback(const char *filename, void *data) {
	Texture *texture = (Texture *)data;
	glDeleteTextures(1, &texture->id);
	load_texture_base(filename, &texture->id, &texture->width, &texture->height);
}

Texture *load_texture(const char *filename) {
    for(int i = 0; i < textures.count; i++) {
        if(textures[i]->filename == filename) return textures[i];
    }
    
    uint id = -1;
    int width = 0, height = 0;
    load_texture_base(filename, &id, &width, &height);
    
    Texture *texture = alloc(Texture);
    texture->id = id;
    texture->width = width;
    texture->height = height;
    array_add(&textures, texture);
    hotload_add_file(filename, (void *)texture, texture_hotload_callback);
    
    return texture;
}