#include "light.h"

namespace BD3GE {
	Light::Light() : light_type(Light::TYPE::DIRECTIONAL), name("Light"), is_active(false), position(Vector3(0.0f, 0.0f, 0.0f)), color_ambient(Color(0, 0, 0)), color_diffuse(Color(0, 0, 0)), color_specular(Color(0, 0, 0)) {}

	Light::Light(Light::TYPE light_type, std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular) {
		this->light_type = light_type;
		this->name = name;
		this->is_active = true;
		this->position = position;
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
	}

	Light::Light(Light::TYPE light_type, std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular, float attenuation_constant, float attenuation_linear, float attenuation_quadratic) : Light(light_type, name, position, color_ambient, color_diffuse, color_specular) {
		this->attenuation_constant = attenuation_constant;
		this->attenuation_linear = attenuation_linear;
		this->attenuation_quadratic = attenuation_quadratic;
	}

	Light::Light(Light::TYPE light_type, std::string name, Vector3 position, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular) : Light(light_type, name, position, color_ambient, color_diffuse, color_specular) {
		this->direction = direction;
	}

	Light::Light(Light::TYPE light_type, std::string name, Vector3 position, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular, float inner_cutoff, float outer_cutoff) : Light(light_type, name, position, direction, color_ambient, color_diffuse, color_specular) {
		this->direction = direction;
		this->inner_cutoff = inner_cutoff;
		this->outer_cutoff = outer_cutoff;
	}
}