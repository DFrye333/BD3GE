#include "material.h"

namespace BD3GE {
	SimpleMaterial::SimpleMaterial() : color_ambient(Vector3(0.1f, 0.1f, 0.1f)), color_diffuse(Vector3(1.0f, 1.0f, 1.0f)), color_specular(Vector3(0.5f, 0.5f, 0.5f)), gloss_factor(32.0f) {}

	SimpleMaterial::SimpleMaterial(Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular, float gloss_factor) {
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
		this->gloss_factor = gloss_factor;
	}

	MappedMaterial::MappedMaterial() : map_diffuse(nullptr), map_specular(nullptr), gloss_factor(32.0f) {}

	MappedMaterial::~MappedMaterial() {
		delete map_diffuse;
		map_diffuse = nullptr;

		delete map_specular;
		map_specular = nullptr;
	}

	MappedMaterial::MappedMaterial(std::string map_diffuse_file_path, std::string map_specular_file_path, float gloss_factor) {
		this->map_diffuse = new Texture(map_diffuse_file_path);
		this->map_specular = new Texture(map_specular_file_path);
		this->gloss_factor = gloss_factor;
	}
}