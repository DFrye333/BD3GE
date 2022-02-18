#version 460 core

struct Light {
	vec3 position;
	bool is_active;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float attenuation_constant;
	float attenuation_linear;
	float attenuation_quadratic;
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
uniform unsigned int quantity_lights;
uniform Light lights[8];
uniform MappedMaterial material;

in vec2 texture_coordinates;

smooth in vec4 world_position;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	if (quantity_lights == 0) { fragment_color = vec4(vec3(texture(material.map_diffuse, texture_coordinates)), 1.0); return; }

	fragment_color = vec4(vec3(texture(material.map_diffuse, texture_coordinates)) * 0.1, 1);

	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = normal_matrix * normalize(normal);
	vec3 view_direction = normalize(viewer_position - world_position.xyz);

	for (unsigned int i = 0; i < quantity_lights; ++i) {
		if (!lights[i].is_active) { continue; }

		vec3 light_direction = lights[i].position - world_position.xyz;

		vec3 ambient_component = lights[i].color_ambient * vec3(texture(material.map_diffuse, texture_coordinates));

		vec3 diffuse_component = lights[i].color_diffuse * max(0.0, dot(normal_vector, normalize(light_direction))) * vec3(texture(material.map_diffuse, texture_coordinates));

		vec3 reflection_direction = normalize(reflect(-light_direction, normal_vector));
		float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
		vec3 specular_component = vec3(texture(material.map_specular, texture_coordinates)) * specular_factor * lights[i].color_specular;

		float light_distance = length(light_direction);
		float attenuation_factor = 1.0 / (lights[i].attenuation_constant + (light_distance * lights[i].attenuation_linear) + ((light_distance * light_distance) * lights[i].attenuation_quadratic));

		fragment_color += vec4(ambient_component + diffuse_component + specular_component, 1.0);
	}
}