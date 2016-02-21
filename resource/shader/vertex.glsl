#version 440

uniform vec3 offset;
uniform mat4 transformation_matrix;

layout(location = 0) in vec4 in_position;
layout(location = 1) uniform vec4 in_color;

smooth out vec4 vertex_color;

void main(void)
{
	vec4 camera_position = in_position + vec4(offset.x, offset.y, offset.z, 1.0f);
	gl_Position = transformation_matrix * camera_position;

	vertex_color = in_color;
}