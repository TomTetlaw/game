#ifndef FONT_H
#define FONT_H

struct Font {
    const char *filename = null;
    int point_size = 0;
};

void font_shutdown();
Font *load_font(const char *filename, int point_size);

#endif