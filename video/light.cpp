#include "light.h"

namespace BD3GE {
	Light::Light() : position(Vector3(0.0f, 0.0f, 0.0f)), color_ambient(Vector3(0.0f, 0.0f, 0.0f)), color_diffuse(Vector3(0.0f, 0.0f, 0.0f)), color_specular(Vector3(0.0f, 0.0f, 0.0f)) {}

	Light::Light(Vector3 position, Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular) {
		this->position = position;
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
	}
}