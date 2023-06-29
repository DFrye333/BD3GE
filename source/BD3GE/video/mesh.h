#ifndef BD3GE_MESH_H
#define BD3GE_MESH_H

#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/renderable.h"

namespace BD3GE {
	class Mesh : public RenderableUnit {
		public:
			Mesh();
			Mesh(Material* material);
			Mesh(Material* material, const aiMesh* mesh, TransformNode* transform_node);
	};
}

#endif // BD3GE_MESH_H