#version 460

in vec4 position;
in vec4 colour;
in vec2 tex_coord;
in vec3 normal;

uniform float time;

out vec4 frag_colour;

void main(void) {
	frag_colour = colour;
}