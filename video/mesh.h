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

					Mesh(const aiMesh* mesh);
					~Mesh();
			void	setup();
			void	render(Transform world_view_projection_transform);

		private:

			Transform	m_model_transform;
			GLuint		m_VBO_position;
			GLuint		m_IBO_position;
			GLuint		m_VAO;
			GLfloat*	m_vertex_position_buffer;
			GLuint*		m_index_position_buffer;
			GLuint		m_num_vertices;
			GLuint		m_num_indices;
			Shader*		m_shader;
	};
}

#endif // BD3GE_MESH_H
