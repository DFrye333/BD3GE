#ifndef BD3GE_MATERIAL_H
#define BD3GE_MATERIAL_H

#include "../utility/vector.h"

namespace BD3GE {
	class Material {
		public:
			Material();
			Material(Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular, float gloss_factor);

			Vector3 color_ambient;
			Vector3 color_diffuse;
			Vector3 color_specular;
			float gloss_factor;
	};
}

#endif // BD3GE_MATERIAL_H