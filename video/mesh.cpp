#include "mesh.h"

namespace BD3GE
{
	/*
	 *	Mesh class
	 */

	Mesh::Mesh(const aiMesh* mesh)
	{
		g_log.write(BD3GE::LOG_TYPE::INFO, "Loading mesh with " + std::to_string(mesh->mNumVertices) + " vertices and " + std::to_string(mesh->mNumFaces) + " faces...");

		// Fill vertex position buffer.
		m_num_vertices = mesh->mNumVertices;
		m_vertex_position_buffer = new GLfloat[4 * m_num_vertices];
		for (unsigned int i = 0; i < m_num_vertices; ++i)
		{
			m_vertex_position_buffer[(4 * i) + 0]	= (GLfloat)(mesh->mVertices[i].x);
			m_vertex_position_buffer[(4 * i) + 1]	= (GLfloat)(mesh->mVertices[i].y);
			m_vertex_position_buffer[(4 * i) + 2]	= (GLfloat)(mesh->mVertices[i].z);
			m_vertex_position_buffer[(4 * i) + 3]	= 1.0f;
		}

		// Determine the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		m_num_indices = 0;
		for (unsigned int i = 0; i < num_faces; ++i)
		{
			m_num_indices += mesh->mFaces[i].mNumIndices;
		}

		// Fill index position buffer.
		m_index_position_buffer = new GLuint[m_num_indices];
		for (unsigned int i = 0; i < num_faces; ++i)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			{
				m_index_position_buffer[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}

		// Generate VAO.
		glGenVertexArrays(1, &m_VAO);

		// Generate VBOs.
		glGenBuffers(1, &m_VBO_position);
		glGenBuffers(1, &m_IBO_position);

		// Setup for VAO.
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_position);
		glBufferData(GL_ARRAY_BUFFER, 4 * m_num_vertices * sizeof(GLfloat), m_vertex_position_buffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO_position);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_num_indices * sizeof(GLuint), m_index_position_buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		// Cleanup for VAO.
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_shader = new Shader;
	}

	Mesh::~Mesh()
	{
		delete[] m_vertex_position_buffer;
		m_vertex_position_buffer = NULL;

		delete[] m_index_position_buffer;
		m_index_position_buffer = NULL;

		delete m_shader;
		m_shader = NULL;
	}

	void Mesh::render(Transform world_view_projection_transform)
	{
		// Setup for shader program.
		glUseProgram(m_shader->get_program_ID());

		GLfloat transformation_array[16];
		world_view_projection_transform.to_float_array(transformation_array);

		glUniformMatrix4fv(glGetUniformLocation(m_shader->get_program_ID(), "transformation_matrix"), 1, GL_TRUE, transformation_array);

		// Update position.
		glUniform3f(glGetUniformLocation(m_shader->get_program_ID(), "offset"), world_view_projection_transform(3, 0), world_view_projection_transform(3, 1), world_view_projection_transform(3, 2));

		glUniform4f(glGetUniformLocation(m_shader->get_program_ID(), "in_color"), 0.0f, 1.0f, 0.0f, 1.0f);

		// Draw mesh using its VAO.
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		glUseProgram(0);
	}
}