#ifndef BD3GE_LIGHT_H
#define BD3GE_LIGHT_H

#include "../utility/color.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Light {
		public:
			enum class TYPE {
				DIRECTIONAL,
				POINT,
				SPOT
			};

			Light();
			Light(std::string name, Color color_ambient, Color color_diffuse, Color color_specular);

			Light::TYPE type;
			std::string name;
			bool is_active;
			Color color_ambient;
			Color color_diffuse;
			Color color_specular;
	};

	class DirectionalLight : public Light {
		public:
			DirectionalLight(std::string name, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular);

			Vector3 direction;
	};

	class PointLight : public Light {
		public:
			PointLight(std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular, float attenuation_constant = 1.0f, float attenuation_linear = 0.001f, float attenuation_quadratic = 0.000001f);

			Vector3 position;
			float attenuation_constant;
			float attenuation_linear;
			float attenuation_quadratic;
	};

	class SpotLight : public Light {
		public:
			SpotLight(std::string name, Vector3 position, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular, float inner_cutoff = 10.0f, float outer_cutoff = 12.5f);

			Vector3 position;
			Vector3 direction;
			float inner_cutoff;
			float outer_cutoff;
	};
}

#endif // BD3GE_LIGHT_H