#ifndef BD3GE_LIGHT_H
#define BD3GE_LIGHT_H

#include "../utility/color.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Light {
		public:

			Light();
			Light(Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular);
			Light(Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular, float attenuation_constant, float attenuation_linear, float attenuation_quadratic);

			Vector3 position;
			Color color_ambient;
			Color color_diffuse;
			Color color_specular;
			float attenuation_constant = 1.0f;
			float attenuation_linear = 0.001f;
			float attenuation_quadratic = 0.000001f;
	};
}

#endif // BD3GE_LIGHT_H