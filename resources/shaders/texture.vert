#version 460 core

uniform mat4 world_transform;
uniform mat4 view_projection_transform;

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_texture_coordinates;

smooth out vec4 world_position;
smooth out vec2 texture_coordinates;

void main(void) {
	world_position = world_transform * vec4(in_position.xyz, 1.0);
	gl_Position = view_projection_transform * world_position;

	texture_coordinates = in_texture_coordinates;
}