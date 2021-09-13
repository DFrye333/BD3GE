#version 460 core

smooth in vec4 color;

out vec4 fragment_color;

void main(void) {
	// float lerpValue = (gl_FragCoord.y - 300.0) / 300.0f;
	//fragment_color = mix(vertex_color, vec4(1.0f, 1.0f, 1.0f, 1.0f), lerpValue);

	fragment_color = color;
}