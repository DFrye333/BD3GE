#version 460 core

in vec2 texture_coordinates;

out vec4 fragment_color;

uniform sampler2D tex;

void main(void) {
	fragment_color = texture(tex, texture_coordinates);
}