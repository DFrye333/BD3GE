#version 460

uniform in vec4 vertex_color;

out vec4 fragment_color;

void main(void)
{
	// float lerpValue = (gl_FragCoord.y - 300.0) / 300.0f;
	
	// fragment_color = mix(vertex_color, vec4(1.0f, 1.0f, 1.0f, 1.0f), lerpValue);
	// fragment_color = mix(vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), lerpValue);
	fragment_color = vertex_color;
}