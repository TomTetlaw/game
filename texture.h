#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture {
    uint id = 0;
    int width = 0;
    int height = 0;
    const char *filename = null;
};

void tex_init();
void tex_shutdown();
Texture *load_texture(const char *filename);

#endif
