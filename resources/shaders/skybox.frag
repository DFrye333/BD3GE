#version 460 core

smooth in vec3 texture_coordinates;

uniform samplerCube skybox;

out vec4 fragment_color;

void main() {
	fragment_color = texture(skybox, texture_coordinates);
}