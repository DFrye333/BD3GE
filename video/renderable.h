#ifndef BD3GE_RENDERABLE_H
#define BD3GE_RENDERABLE_H

#include <glew/GL/glew.h>
#include "../utility/object.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/shader.h"
#include "../video/vertex.h"

namespace BD3GE {
	class Renderable : public Object {
		public:
			Renderable();
			Renderable(Vector3 position);
			virtual ~Renderable();
			void setup();
			virtual void render(Transform view_projection_transform) const;

			std::vector<Material*> materials;
			unsigned int vao_handle;
			Vertex* vbo;
			unsigned int* ibo;
			unsigned int num_vertices;
			unsigned int num_indices;
	};
}

#endif // BD3GE_RENDERABLE_H