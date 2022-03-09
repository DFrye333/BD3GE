#ifndef BD3GE_RENDERABLE_H
#define BD3GE_RENDERABLE_H

#include <vector>

#include <glew/GL/glew.h>

#include "../system/api.h"
#include "../utility/object.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/shader.h"
#include "../video/vertex.h"

namespace BD3GE {
	struct RenderableGeometry {
		unsigned int vao_handle;
		unsigned int num_vertices;
		unsigned int num_indices;
		unsigned int* ibo = nullptr;
		Vertex* vbo = nullptr;
	};

	class RenderableUnit {
		public:
			RenderableUnit();
			RenderableUnit(Material* material);
			RenderableUnit(Material* material, TransformNode* transform_node);
			RenderableUnit(const RenderableUnit& other);
			virtual ~RenderableUnit();
			const RenderableUnit& operator=(const RenderableUnit& other);

			RenderableGeometry geometry;
			Material* material = nullptr;
			TransformNode* transform_node;
	};

	class BD3GE_API Renderable {
		public:
			std::vector<RenderableUnit*> renderable_units;
	};
}

#endif // BD3GE_RENDERABLE_H