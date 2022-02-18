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
			Light(Light::TYPE light_type, std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular);
			Light(Light::TYPE light_type, std::string name, Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular, float attenuation_constant, float attenuation_linear, float attenuation_quadratic);
			Light(Light::TYPE light_type, std::string name, Vector3 position, Vector3 direction, Color color_ambient, Color color_diffuse, Color color_specular, float cone_cutoff);

			Light::TYPE light_type;
			std::string name;
			bool is_active;
			Vector3 position;
			Vector3 direction;
			Color color_ambient;
			Color color_diffuse;
			Color color_specular;
			float attenuation_constant = 1.0f;
			float attenuation_linear = 0.001f;
			float attenuation_quadratic = 0.000001f;
			float cone_cutoff = 12.5f;
	};
}

#endif // BD3GE_LIGHT_H