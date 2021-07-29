#ifndef BD3GE_MESH_H
#define BD3GE_MESH_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/vector3.h>
#include <GL/glew.h>

#include "../system/globals.h"
#include "../utility/matrix.h"
#include "../utility/transform.h"
#include "../video/shader.h"

namespace BD3GE {
	class Mesh {
		public:

						Mesh(Vector3* positions);
						Mesh(const aiMesh* mesh);
						~Mesh();

			GLfloat*	m_vertex_position_buffer;
			GLuint*		m_index_position_buffer;
			GLuint		m_num_vertices;
			GLuint		m_num_indices;
	};
}

#endif // BD3GE_MESH_H
