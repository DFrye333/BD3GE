#include "light.h"

namespace BD3GE {
	Light::Light() : type(Light::TYPE::DIRECTIONAL), name("Light"), is_active(false), color_ambient(Color(0, 0, 0)), color_diffuse(Color(0, 0, 0)), color_specular(Color(0, 0, 0)) {}

	Light::Light(std::string name, Color color_ambient, Color color_diffuse, Color color_specular) {
		this->name = name;
		this->is_active = true;
		this->color_ambient = color_ambient;
		this->color_diffuse = color_diffuse;
		this->color_specular = color_specular;
	}

	DirectionalLight::DirectionalLight(std::string name, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular) : Light(name, color_ambient, color_diffuse, color_specular) {
		this->type = Light::TYPE::DIRECTIONAL;
		this->direction = direction;
	}

	PointLight::PointLight(std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular, float attenuation_constant, float attenuation_linear, float attenuation_quadratic) : Light(name, color_ambient, color_diffuse, color_specular) {
		this->type = Light::TYPE::POINT;
		this->position = position;
		this->attenuation_constant = attenuation_constant;
		this->attenuation_linear = attenuation_linear;
		this->attenuation_quadratic = attenuation_quadratic;
	}

	SpotLight::SpotLight(std::string name, Vector3 position, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular, float inner_cutoff, float outer_cutoff) : Light(name, color_ambient, color_diffuse, color_specular) {
		this->type = Light::TYPE::SPOT;
		this->position = position;
		this->direction = direction;
		this->inner_cutoff = inner_cutoff;
		this->outer_cutoff = outer_cutoff;
	}
}