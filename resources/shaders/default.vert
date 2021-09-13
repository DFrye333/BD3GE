#version 460 core

uniform mat4 world_transform;
uniform mat4 view_projection_transform;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;

out vec4 world_position;
out vec4 color;
out vec3 normal;

void main(void) {
	world_position = world_transform * vec4(in_position.xyz, 1.0);
	gl_Position = view_projection_transform * world_position;
	color = in_color;
	normal = in_normal;
}