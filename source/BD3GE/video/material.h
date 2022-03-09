#ifndef BD3GE_MATERIAL_H
#define BD3GE_MATERIAL_H

#include <assimp/material.h>

#include "../management/texture_manager.h"
#include "../system/api.h"
#include "../system/globals.h"
#include "../utility/color.h"
#include "../utility/log.h"

namespace BD3GE {
	class Material {
		public:
			enum class TYPE {
				SIMPLE,
				MAPPED
			};

			Material();
			Material(size_t shader_id);
			Material(size_t shader_id, float gloss_factor);
			virtual Material* clone() = 0;

			Material::TYPE type;
			size_t shader_id;
			float gloss_factor = 32.0f;
	};

	extern "C" class BD3GE_API SimpleMaterial : public Material {
		public:
			SimpleMaterial(size_t shader_id, Color color);
			SimpleMaterial(size_t shader_id, Color color_ambient, Color color_diffuse, Color color_specular);
			SimpleMaterial(size_t shader_id, Color color_ambient, Color color_diffuse, Color color_specular, float gloss_factor);
			SimpleMaterial(size_t shader_id, aiMaterial* material);
			Material* clone() override;

			Color color_ambient = Color(0.1f, 0.1f, 0.1f);
			Color color_diffuse = Color(1.0f, 1.0f, 1.0f);
			Color color_specular = Color(0.5f, 0.5f, 0.5f);
	};

	extern "C" class BD3GE_API MappedMaterial : public Material {
		public:
			MappedMaterial();
			MappedMaterial(size_t shader_id, size_t map_diffuse_id, size_t map_specular_id, float gloss_factor);
			MappedMaterial(size_t shader_id, aiMaterial* material);
			Material* clone() override;

			size_t map_diffuse_id;
			size_t map_specular_id;
	};
}

#endif // BD3GE_MATERIAL_H