#version 460

uniform mat4 transformation_matrix;

layout(location = 0) in vec4 in_position;
layout(location = 1) uniform vec4 in_color;

smooth out vec4 vertex_color;

void main(void)
{
	gl_Position = transformation_matrix * in_position;

	vertex_color = vec4(in_color.x, in_color.y, in_color.z, in_color.w);
}