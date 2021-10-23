#include "material.h"

namespace BD3GE {
	Material::Material() : color_ambient(Vector3(0.1f, 0.1f, 0.1f)), color_diffuse(Vector3(1.0f, 1.0f, 1.0f)), color_specular(Vector3(0.5f, 0.5f, 0.5f)), gloss_factor(32.0f) {}

	Material::Material(Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular, float gloss_factor) {
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
		this->gloss_factor = gloss_factor;
	}
}