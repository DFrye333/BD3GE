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
		glGenVertexArrays(1, &vaoHandle);

		// Generate VBOs.
		GLuint vboHandle, iboHandle;
		glGenBuffers(1, &vboHandle);
		glGenBuffers(1, &iboHandle);

		// Setup for VAO.
		glBindVertexArray(vaoHandle);

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		glBufferData(GL_ARRAY_BUFFER, sizePerVertex * numVertices * sizeof(GLfloat), vbo, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), ibo, GL_STATIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
	}

	void Renderable::render(Transform view_projection_transform) const {
		for (Material* material : this->materials) {
			// Setup for shader program.
			material->shader->enable();

			material->shader->setUniform("world_transform", this->worldTransform.get_matrix());
			material->shader->setUniform("inverse_world_transform", this->worldTransform.get_matrix().inverse());
			material->shader->setUniform("view_projection_transform", view_projection_transform.get_matrix());

			// TODO: Change this?
			material->prepForRender();
			// Draw mesh using its VAO.
			glBindVertexArray(vaoHandle);
			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Cleanup.
			material->shader->disable();
		}
	}
}