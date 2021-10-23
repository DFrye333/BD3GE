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
			Renderable(Material* material);
			Renderable(Shader* shader, Material* material);
			virtual ~Renderable();
			virtual void render(Transform worldTransform, Transform viewProjectionTransform) const;
			Shader* shader;
			Material* material;
			GLuint vaoHandle;
			GLuint tboHandle;
			GLfloat* vbo;
			GLuint* ibo;
			GLuint numVertices;
			GLuint numIndices;
			GLuint sizePerVertex;

		protected:
			virtual void setup() = 0;
			bool owns_shader;
			bool owns_material;
	};
}

#endif // BD3GE_RENDERABLE_H