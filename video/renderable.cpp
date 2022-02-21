#include "renderable.h"

namespace BD3GE {
	Renderable::Renderable() {}

	Renderable::Renderable(Vector3 position) : Object(position) {}

	Renderable::~Renderable() {
		delete[] vbo;
		vbo = nullptr;

		delete[] ibo;
		ibo = nullptr;
	}

	void Renderable::setup() {
		// Generate VAO.
		glGenVertexArrays(1, &vao_handle);

		// Generate VBOs.
		GLuint vboHandle, iboHandle;
		glGenBuffers(1, &vboHandle);
		glGenBuffers(1, &iboHandle);

		// Setup for VAO.
		glBindVertexArray(vao_handle);

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(Vertex), vbo, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint), ibo, GL_DYNAMIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(0);

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(1);

		// Mapped material
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));
		glEnableVertexAttribArray(2);
	}

	void Renderable::render(Transform view_projection_transform) const {
		for (Material* material : this->materials) {
			// Setup for shader program.
			material->shader->enable();

			material->shader->setUniform("world_transform", this->world_transform.get_matrix());
			material->shader->setUniform("inverse_world_transform", this->world_transform.get_matrix().inverse());
			material->shader->setUniform("view_projection_transform", view_projection_transform.get_matrix());

			// TODO: Change this?
			material->prepForRender();
			// Draw mesh using its VAO.
			glBindVertexArray(vao_handle);
			glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Cleanup.
			material->shader->disable();
		}
	}
}