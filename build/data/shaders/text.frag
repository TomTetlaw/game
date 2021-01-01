#version 460

in vec4 position;
in vec4 colour;
in vec2 tex_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;
uniform float time;

out vec4 frag_colour;

void main(void) {
	float texture_colour = texture(diffuse_texture, tex_coord).r;
	if(texture_colour == 0.0) discard;

	frag_colour = colour * vec4(texture_colour, texture_colour, texture_colour, 1);
}