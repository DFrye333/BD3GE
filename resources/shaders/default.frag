#version 460 core

const unsigned short MAX_QUANTITY_DIRECTIONAL_LIGHTS = unsigned short(8);
const unsigned short MAX_QUANTITY_POINT_LIGHTS = unsigned short(8);
const unsigned short MAX_QUANTITY_SPOT_LIGHTS = unsigned short(8);

struct DirectionalLight {
	bool is_active;
	vec3 position;
	vec3 direction;
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
};

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
	float inner_cutoff;
	float outer_cutoff;
};

struct SimpleMaterial {
	vec3 color_ambient;
	vec3 color_diffuse;
	vec3 color_specular;
	float gloss_factor;
};

struct MappedMaterial {
	sampler2D map_diffuse;
	sampler2D map_specular;
	float gloss_factor;
};

uniform bool is_material_mapped = false;
uniform mat4 world_transform;
uniform mat4 inverse_world_transform;
uniform mat4 view_projection_transform;
uniform vec3 viewer_position;
uniform unsigned int quantity_directional_lights;
uniform unsigned int quantity_point_lights;
uniform unsigned int quantity_spot_lights;
uniform DirectionalLight directional_lights[MAX_QUANTITY_DIRECTIONAL_LIGHTS];
uniform PointLight point_lights[MAX_QUANTITY_POINT_LIGHTS];
uniform SpotLight spot_lights[MAX_QUANTITY_SPOT_LIGHTS];
uniform SimpleMaterial simple_material;
uniform MappedMaterial mapped_material;

smooth in vec4 world_position;
smooth in vec3 normal;
smooth in vec2 texture_coordinates;

out vec4 fragment_color;

void main(void) {
	vec3 material_component_ambient;
	vec3 material_component_diffuse;
	vec3 material_component_specular;
	float material_gloss_factor;

	if (is_material_mapped) {
		material_component_ambient = vec3(texture(mapped_material.map_diffuse, texture_coordinates));
		material_component_diffuse = vec3(texture(mapped_material.map_diffuse, texture_coordinates));
		material_component_specular = vec3(texture(mapped_material.map_specular, texture_coordinates));
		material_gloss_factor = mapped_material.gloss_factor;
	} else {
		material_component_ambient = simple_material.color_ambient;
		material_component_diffuse = simple_material.color_diffuse;
		material_component_specular = simple_material.color_specular;
		material_gloss_factor = simple_material.gloss_factor;
	}

	if (quantity_directional_lights == 0 && quantity_point_lights == 0 && quantity_spot_lights == 0) { fragment_color = vec4(material_component_diffuse, 1.0); return; }

	fragment_color = vec4(material_component_ambient * 0.1, 1);

	mat3 normal_matrix = mat3(transpose(inverse_world_transform));
	vec3 normal_vector = normal_matrix * normalize(normal);
	vec3 view_direction = normalize(viewer_position - world_position.xyz);

	for (unsigned int i = 0; i < quantity_directional_lights; ++i) {
		DirectionalLight light = directional_lights[i];

		if (!light.is_active) { continue; }

		vec3 ambient_component = light.color_ambient * material_component_ambient;

		vec3 diffuse_component = light.color_diffuse * material_component_diffuse;

		float specular_factor = pow(max(0.0, dot(light.direction, -view_direction)), material_gloss_factor);
		vec3 specular_component = light.color_specular * material_component_specular * specular_factor;

		float intensity = clamp(dot(normalize(light.direction), -normal_vector), 0.0f, 1.0f);

		fragment_color += vec4(intensity * (ambient_component + diffuse_component + specular_component), 1.0);
	}

	for (unsigned int i = 0; i < quantity_point_lights; ++i) {
		PointLight light = point_lights[i];

		if (!light.is_active) { continue; }

		vec3 towards_light_direction = light.position - world_position.xyz;

		vec3 ambient_component = light.color_ambient * material_component_ambient;

		vec3 diffuse_component = light.color_diffuse * max(0.0, dot(normal_vector, normalize(towards_light_direction))) * material_component_diffuse;

		vec3 reflection_direction = normalize(reflect(-towards_light_direction, normal_vector));
		float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material_gloss_factor);
		vec3 specular_component = light.color_specular * material_component_specular * specular_factor;

		float light_distance = length(towards_light_direction);
		float attenuation_factor = 1.0 / (light.attenuation_constant + (light_distance * light.attenuation_linear) + ((light_distance * light_distance) * light.attenuation_quadratic));

		fragment_color += vec4(attenuation_factor * (ambient_component + diffuse_component + specular_component), 1.0);
	}

	for (unsigned int i = 0; i < quantity_spot_lights; ++i) {
		SpotLight light = spot_lights[i];

		if (!light.is_active) { continue; }

		vec3 towards_light_direction = normalize(spot_lights[i].position - world_position.xyz);
		float light_center_offset = dot(light.direction, -towards_light_direction);

		if (light_center_offset > light.outer_cutoff) {
			vec3 ambient_component = light.color_ambient * material_component_ambient;

			vec3 diffuse_component = light.color_diffuse * max(0.0, dot(normal_vector, normalize(towards_light_direction))) * material_component_diffuse;

			vec3 reflection_direction = normalize(reflect(-towards_light_direction, normal_vector));
			float specular_factor = pow(max(0.0, dot(reflection_direction, view_direction)), material_gloss_factor);
			vec3 specular_component = light.color_specular * material_component_specular * specular_factor;

			float intensity = clamp((light_center_offset - light.outer_cutoff) / (light.inner_cutoff - light.outer_cutoff), 0.0f, 1.0f);

			fragment_color += vec4(intensity * (ambient_component + diffuse_component + specular_component), 1.0);
		}
	}
}