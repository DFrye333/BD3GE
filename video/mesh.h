#ifndef BD3GE_MESH_H
#define BD3GE_MESH_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/vector3.h>
#include <GL/glew.h>

#include "../system/globals.h"
#include "../utility/matrix.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/shader.h"
#include "../video/drawable.h"

namespace BD3GE {
	class Mesh : public Drawable {
		public:

			Mesh(const aiMesh* mesh, Vector3 scale);

			GLfloat	scale;
	};
}

#endif // BD3GE_MESH_H
