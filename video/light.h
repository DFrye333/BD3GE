#ifndef BD3GE_LIGHT_H
#define BD3GE_LIGHT_H

#include "../utility/vector.h"

namespace BD3GE {
	class Light {
		public:

			Light();
			Light(Vector3 position, Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular);

			Vector3 position;
			Vector3 color_ambient;
			Vector3 color_diffuse;
			Vector3 color_specular;
	};
}

#endif // BD3GE_LIGHT_H