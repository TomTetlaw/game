#ifndef RENDER_H
#define RENDER_H

struct Program {
	const char *vertex_filename = nullptr;
	const char *frag_filename = nullptr;
	unsigned int vertex_object = 0;
	unsigned int frag_object = 0;
	unsigned int program_object = 0;
};

struct Vertex {
	Vec3 position;
	Vec4 colour;
	Vec2 uv;
	Vec3 normal;
};

struct Texture;
struct RC_Texture {
	Texture *texture = nullptr;
	int first_index = 0;
};

enum Render_Command_Type {
	RC_TEXTURE,
};

struct Render_Command {
	Render_Command() {}
    
	Render_Command_Type type;
    
	union {
		RC_Texture texture;
	};
};

extern int window_width;
extern int window_height;

void r_init();
void r_shutdown();
void r_execute_commands();

void r_begin_frame();
void r_end_frame();

void setup_program(Program *program, const char *vert_filename, const char *frag_filename);
void set_program(Program *program);

void r_render_texture(Texture *texture, Vec2 position);

#endif
