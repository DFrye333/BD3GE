#include "mesh.h"

namespace BD3GE {
	/*
	 *	Mesh class
	 */

	Mesh::Mesh(const aiMesh* mesh) {
		g_log.write(BD3GE::LOG_TYPE::INFO, "Loading mesh with " + std::to_string(mesh->mNumVertices) + " vertices and " + std::to_string(mesh->mNumFaces) + " faces...");

		// Fill vertex position buffer.
		m_num_vertices = mesh->mNumVertices;
		m_vertex_position_buffer = new GLfloat[4 * m_num_vertices];
		for (unsigned int i = 0; i < m_num_vertices; ++i) {
			m_vertex_position_buffer[(4 * i) + 0]	= (GLfloat)(mesh->mVertices[i].x);
			m_vertex_position_buffer[(4 * i) + 1]	= (GLfloat)(mesh->mVertices[i].y);
			m_vertex_position_buffer[(4 * i) + 2]	= (GLfloat)(mesh->mVertices[i].z);
			m_vertex_position_buffer[(4 * i) + 3]	= 1.0f;
		}

		// Determine the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		m_num_indices = 0;
		for (unsigned int i = 0; i < num_faces; ++i) {
			m_num_indices += mesh->mFaces[i].mNumIndices;
		}

		// Fill index position buffer.
		m_index_position_buffer = new GLuint[m_num_indices];
		for (unsigned int i = 0; i < num_faces; ++i) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
				m_index_position_buffer[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}
	}

	Mesh::~Mesh() {
		delete[] m_vertex_position_buffer;
		m_vertex_position_buffer = NULL;

		delete[] m_index_position_buffer;
		m_index_position_buffer = NULL;
	}
}