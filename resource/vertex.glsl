#version 440

uniform vec3 offset;
uniform mat4 perspectiveMatrix;

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inColor;

smooth out vec4 color;

void main(void)
{
	vec4 cameraPos = inPosition + vec4(offset.x, offset.y, offset.z, 1.0f);
	
	gl_Position = perspectiveMatrix * cameraPos;
	
    color = inColor;
}