#ifndef BD3GE_LIGHT_H
#define BD3GE_LIGHT_H

#include "../utility/color.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Light {
		public:

			Light();
			Light(Vector3 position, Color color_ambient, Color color_diffuse, Color color_specular);

			Vector3 position;
			Color color_ambient;
			Color color_diffuse;
			Color color_specular;
	};
}

#endif // BD3GE_LIGHT_H