#version 460 core

struct Light {
	vec3 position;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float attenuation_constant;
	float attenuation_linear;
	float attenuation_quadratic;
};

struct SimpleMaterial {
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float gloss_factor;
};

uniform mat4 world_transform;
uniform mat4 inverse_world_transform;
uniform mat4 view_projection_transform;
uniform vec3 viewer_position;
uniform Light light;
uniform SimpleMaterial material;

smooth in vec4 world_position;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = normal_matrix * normalize(normal);
	vec3 light_direction = light.position - world_position.xyz;

	vec3 ambient_component = light.color_ambient * material.color_ambient;

	vec3 diffuse_component = light.color_diffuse * max(0.0, dot(normal_vector, normalize(light_direction))) * material.color_diffuse;

	vec3 reflection_direction = normalize(reflect(-light_direction, normal_vector));
	vec3 view_direction = normalize(viewer_position - world_position.xyz);
	float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
	vec3 specular_component = light.color_specular * specular_factor * material.color_specular;

	float light_distance = length(light_direction);
	float attenuation_factor = 1.0 / (light.attenuation_constant + (light_distance * light.attenuation_linear) + ((light_distance * light_distance) * light.attenuation_quadratic));

	fragment_color = vec4(attenuation_factor * (ambient_component + diffuse_component + specular_component), 1.0);
}