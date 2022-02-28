#version 460 core

struct SimpleMaterial {
	vec3 color_ambient;
};

struct MappedMaterial {
	sampler2D map_diffuse[8];
};

uniform bool is_material_mapped = false;
uniform SimpleMaterial simple_material;
uniform MappedMaterial mapped_material;

smooth in vec2 texture_coordinates;

out vec4 fragment_color;

void main(void) {
	fragment_color = vec4(
		is_material_mapped ? vec3(texture(mapped_material.map_diffuse[0], texture_coordinates)) : simple_material.color_ambient,
		1
	);
}