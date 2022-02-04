#ifndef BD3GE_RENDERABLE_H
#define BD3GE_RENDERABLE_H

#include <GL/glew.h>

#include "../utility/object.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/shader.h"

namespace BD3GE {
	class Renderable : public Object {
		public:
			Renderable();
			Renderable(Vector3 position);
			virtual ~Renderable();
			void setup();
			virtual void render(Transform view_projection_transform) const;

			GLuint vaoHandle;
			GLfloat* vbo;
			GLuint* ibo;
			GLuint numVertices;
			GLuint numIndices;
			GLuint sizePerVertex;
			std::vector<Material*> materials;
	};
}

#endif // BD3GE_RENDERABLE_H