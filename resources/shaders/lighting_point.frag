#version 460 core

uniform mat4 world_transform;
uniform mat4 inverse_world_transform;
uniform mat4 view_projection_transform;
uniform vec3 viewer_position;
uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 light_direction;

smooth in vec4 world_position;
smooth in vec4 color;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	float ambient_strength = 0.1;
	vec3 ambient_component = ambient_strength * light_color;

	float diffuse_strength = 1;
	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = mat3(world_transform) * (normal_matrix * normalize(normal));
	vec3 light_direction = light_position - world_position.xyz;
	vec3 diffuse_component = (max(0.0, dot(normal_vector, normalize(light_direction))) * light_color) / ((1.01 - clamp(diffuse_strength, 0, 1)) * length(light_direction));

	float specular_strength = 0.5;
	int gloss_factor = 32;
	vec3 reflection_direction = normalize(reflect(-light_direction, normal_vector));
	vec3 view_direction = normalize(viewer_position - world_position.xyz);
	float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), gloss_factor);
	vec3 specular_component = specular_strength * specular_factor * light_color;

	fragment_color = vec4((ambient_component + diffuse_component + specular_component) * color.xyz, 1.0);
}