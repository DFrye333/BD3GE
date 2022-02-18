#version 460 core

struct PointLight {
	bool is_active;
	vec3 position;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float attenuation_constant;
	float attenuation_linear;
	float attenuation_quadratic;
};

struct SpotLight {
	bool is_active;
	vec3 position;
	vec3 direction;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float cone_cutoff;
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
uniform unsigned int quantity_point_lights;
uniform unsigned int quantity_spot_lights;
uniform PointLight point_lights[8];
uniform SpotLight spot_lights[8];
uniform SimpleMaterial material;

smooth in vec4 world_position;
smooth in vec3 normal;

out vec4 fragment_color;

void main(void) {
	if (quantity_point_lights == 0) { fragment_color = vec4(material.color_diffuse, 1.0); return; }

	fragment_color = vec4(material.color_ambient * 0.1, 1);

	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = normal_matrix * normalize(normal);
	vec3 view_direction = normalize(viewer_position - world_position.xyz);

	for (unsigned int i = 0; i < quantity_point_lights; ++i) {
		PointLight light = point_lights[0];

		if (!point_lights[i].is_active) { continue; }

		vec3 towards_light_direction = light.position - world_position.xyz;

		vec3 ambient_component = light.color_ambient * material.color_ambient;

		vec3 diffuse_component = light.color_diffuse * max(0.0, dot(normal_vector, normalize(towards_light_direction))) * material.color_diffuse;

		vec3 reflection_direction = normalize(reflect(-towards_light_direction, normal_vector));
		float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
		vec3 specular_component = light.color_specular * specular_factor * material.color_specular;

		float light_distance = length(towards_light_direction);
		float attenuation_factor = 1.0 / (light.attenuation_constant + (light_distance * light.attenuation_linear) + ((light_distance * light_distance) * light.attenuation_quadratic));

		fragment_color += vec4(attenuation_factor * (ambient_component + diffuse_component + specular_component), 1.0);
	}

	for (unsigned int i = 0; i < quantity_spot_lights; ++i) {
		SpotLight light = spot_lights[0];

		vec3 towards_light_direction = normalize(spot_lights[i].position - world_position.xyz);

		if (dot(light.direction, -towards_light_direction) > light.cone_cutoff) {
			vec3 ambient_component = light.color_ambient * material.color_ambient;

			vec3 diffuse_component = light.color_diffuse * max(0.0, dot(normal_vector, normalize(towards_light_direction))) * material.color_diffuse;

			vec3 reflection_direction = normalize(reflect(-towards_light_direction, normal_vector));
			float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material.gloss_factor);
			vec3 specular_component = light.color_specular * specular_factor * material.color_specular;

			float light_distance = length(towards_light_direction);

			fragment_color += vec4(ambient_component + diffuse_component + specular_component, 1.0);
		}
	}
}