#ifndef BD3GE_MESH_H
#define BD3GE_MESH_H

#include <assimp/mesh.h>
#include <assimp/texture.h>
#include <assimp/vector3.h>
#include <GL/glew.h>

#include "../system/globals.h"
#include "../utility/matrix.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/renderable.h"
#include "../video/shader.h"
#include "../video/texture.h"

namespace BD3GE {
	class Mesh : public Renderable {
		public:
			Mesh(Vector3 position, const aiMesh* mesh, aiTexture* texture, SimpleMaterial* simpleMaterial, Vector3 scale);

			aiTexture* texture;
	};
}

#endif // BD3GE_MESH_H