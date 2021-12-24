#ifndef BD3GE_MATERIAL_H
#define BD3GE_MATERIAL_H

#include "../utility/vector.h"
#include "../video/texture.h"

namespace BD3GE {
	class SimpleMaterial {
		public:
			SimpleMaterial();
			SimpleMaterial(Vector3 color_ambient, Vector3 color_diffuse, Vector3 color_specular, float gloss_factor);

			Vector3 color_ambient;
			Vector3 color_diffuse;
			Vector3 color_specular;
			float gloss_factor;
	};

	class MappedMaterial {
		public:
			MappedMaterial();
			MappedMaterial(std::string map_diffuse_file_path, std::string map_specular_file_path, float gloss_factor);
			~MappedMaterial();

			Texture* map_diffuse;
			Texture* map_specular;
			float gloss_factor;
	};
}

#endif // BD3GE_MATERIAL_H