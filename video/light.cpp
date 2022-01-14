#include "light.h"

namespace BD3GE {
	Light::Light() : position(Vector3(0.0f, 0.0f, 0.0f)), color_ambient(Color(0, 0, 0)), color_diffuse(Color(0, 0, 0)), color_specular(Color(0, 0, 0)) {}

	Light::Light(Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular) {
		this->position = position;
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
	}
}