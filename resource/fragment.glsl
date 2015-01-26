#version 440

uniform vec4 color;

out vec4 finalColor;

void main(void)
{
	float lerpValue = gl_FragCoord.y / 500.0f;
    
    finalColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
    finalColor = color;
}