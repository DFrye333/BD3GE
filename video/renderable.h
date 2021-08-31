#ifndef BD3GE_RENDERABLE_H
#define BD3GE_RENDERABLE_H

#include <GL/glew.h>

#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/shader.h"

namespace BD3GE {
	class Renderable {
		public:
			Renderable();
			Renderable(Shader* shader);
			virtual ~Renderable();
			virtual void render(Transform worldViewProjectionTransform);

			Shader* shader;
			GLuint vaoHandle;
			GLuint tboHandle;
			GLfloat* vbo;
			GLuint* ibo;
			GLuint numVertices;
			GLuint numIndices;
			GLuint sizePerVertex;

		protected:
			virtual void setup() = 0;
	};
}

#endif // BD3GE_RENDERABLE_H