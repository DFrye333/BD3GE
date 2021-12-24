#ifndef BD3GE_RENDERABLE_H
#define BD3GE_RENDERABLE_H

#include <GL/glew.h>

#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/shader.h"

namespace BD3GE {
	class Renderable {
		public:
			Renderable();
			Renderable(Shader* shader);
			Renderable(SimpleMaterial* material);
			Renderable(Shader* shader, SimpleMaterial* material);
			Renderable(Shader* shader, MappedMaterial* material);
			virtual ~Renderable();
			void setup();
			void addTexture(int textureId, Texture* texture);
			virtual void render(Transform worldTransform, Transform viewProjectionTransform) const;
			void setMaterial(SimpleMaterial* simpleMaterial);
			void setMaterial(MappedMaterial* mappedMaterial);

			Shader* shader;
			SimpleMaterial* simpleMaterial;
			MappedMaterial* mappedMaterial;
			GLuint vaoHandle;
			std::vector<GLuint> tboHandles;
			GLfloat* vbo;
			GLuint* ibo;
			GLuint numVertices;
			GLuint numIndices;
			GLuint sizePerVertex;

		protected:
			bool owns_shader;
			bool owns_simple_material;
			bool owns_mapped_material;
	};
}

#endif // BD3GE_RENDERABLE_H