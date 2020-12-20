#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_colour;
layout(location = 2) in vec2 vertex_tex_coord;
layout(location = 3) in vec3 vertex_normal;

uniform mat4 projection_matrix;
uniform mat4 worldview_matrix;
uniform mat4 transformation_matrix;
uniform float time;

out vec4 position;
out vec4 colour;
out vec2 tex_coord;
out vec3 normal;
out vec3 diffuse;

void main(void) {
	position = projection_matrix * worldview_matrix * transformation_matrix * vec4(vertex_position, 1);

	colour = vertex_colour;  
	tex_coord = vertex_tex_coord.xy;
	normal = vertex_normal;

	gl_Position = position;
}