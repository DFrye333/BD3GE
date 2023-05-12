#version 460 core

uniform mat4 world_transform;
uniform mat4 view_projection_transform;

layout(location = 0) in vec3 in_position;

smooth out vec3 texture_coordinates;

void main() {
	vec4 world_position = world_transform * vec4(in_position, 1.0);
	gl_Position = view_projection_transform * world_position;
	texture_coordinates = vec3(world_position);
}