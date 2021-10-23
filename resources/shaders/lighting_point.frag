#version 460 core

struct Light {
	vec3 position;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
};

struct Material {
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
uniform Material material;
//uniform vec3 light_direction;

smooth in vec4 world_position;
smooth in vec4 color;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	vec3 ambient_component = material.color_ambient * light.color_ambient;

	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = mat3(world_transform) * (normal_matrix * normalize(normal));
	vec3 light_direction = light.position - world_position.xyz;
	vec3 diffuse_component = (max(0.0, dot(normal_vector, normalize(light_direction))) * light.color_diffuse) / ((1.01 - clamp(material.color_diffuse, 0, 1)) * length(light_direction));

	vec3 reflection_direction = normalize(reflect(-light_direction, normal_vector));
	vec3 view_direction = normalize(viewer_position - world_position.xyz);
	float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
	vec3 specular_component = material.color_specular * specular_factor * light.color_specular;

	fragment_color = vec4((ambient_component + diffuse_component + specular_component) * color.xyz, 1.0);
}