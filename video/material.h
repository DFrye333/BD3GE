#ifndef BD3GE_MATERIAL_H
#define BD3GE_MATERIAL_H

#include <assimp/material.h>

#include "../utility/color.h"
#include "../video/shader.h"
#include "../video/texture.h"

namespace BD3GE {
	class Material {
		public:
			Material();
			Material(Shader* shader);
			Material(Shader* shader, int gloss_factor);
			~Material();
			virtual void prepForRender() = 0;

			Shader* shader;
			float gloss_factor = 32.0f;
	};

	class SimpleMaterial : public Material {
		public:
			SimpleMaterial(Shader* shader, Color color);
			SimpleMaterial(Shader* shader, Color color_ambient, Color color_diffuse, Color color_specular);
			SimpleMaterial(Shader* shader, Color color_ambient, Color color_diffuse, Color color_specular, float gloss_factor);
			SimpleMaterial(Shader* shader, aiMaterial* material);
			void setup();
			void prepForRender();

			Color color_ambient = Color(0.1f, 0.1f, 0.1f);
			Color color_diffuse = Color(1.0f, 1.0f, 1.0f);
			Color color_specular = Color(0.5f, 0.5f, 0.5f);
	};

	class MappedMaterial : public Material {
		public:
			MappedMaterial();
			MappedMaterial(Shader* shader, Texture* map_diffuse, Texture* map_specular, float gloss_factor);
			void prepForRender() override;

			Texture* map_diffuse;
			Texture* map_specular;
	};
}

#endif // BD3GE_MATERIAL_H