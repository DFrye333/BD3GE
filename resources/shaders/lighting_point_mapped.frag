#version 460 core

struct Light {
	vec3 position;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
};

struct MappedMaterial {
	sampler2D map_diffuse;
	sampler2D map_specular;
	float gloss_factor;
};

uniform mat4 world_transform;
uniform mat4 inverse_world_transform;
uniform mat4 view_projection_transform;
uniform vec3 viewer_position;
uniform Light light;
uniform MappedMaterial material;

in vec2 texture_coordinates;

smooth in vec4 world_position;
smooth in vec4 color;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	// TODO: Need real normal vector, rather than constant (0, 0, 1)
	vec3 normal_vector = normal_matrix * normalize(vec3(0, 0, 1));
	vec3 light_direction = light.position - world_position.xyz;

	vec3 ambient_component = vec3(texture(material.map_diffuse, texture_coordinates)) * light.color_ambient;

	vec3 diffuse_component = (max(0.0, dot(normal_vector, normalize(light_direction))) * light.color_diffuse) / ((1.01 - clamp(vec3(texture(material.map_diffuse, texture_coordinates)), 0, 1)) * length(light_direction));

	vec3 reflection_direction = normalize(reflect(-light_direction, normal_vector));
	vec3 view_direction = normalize(viewer_position - world_position.xyz);
	float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
	vec3 specular_component = vec3(texture(material.map_specular, texture_coordinates)) * specular_factor * light.color_specular;

	fragment_color = vec4(ambient_component + diffuse_component + specular_component, 1.0);
}