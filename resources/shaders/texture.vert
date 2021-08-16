#version 460

uniform mat4 transformation_matrix;

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_texture_coordinates;

smooth out vec4 vertex_color;
smooth out vec2 texture_coordinates;

void main(void) {
	gl_Position = transformation_matrix * in_position;

	vertex_color = vec4(in_color.x, in_color.y, in_color.z, in_color.w);
	texture_coordinates = in_texture_coordinates;
}