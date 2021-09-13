#include "renderable.h"

namespace BD3GE {
	Renderable::Renderable() : Renderable(new Shader(DEFAULT_RESOURCE_DIRECTORY + "shaders/default.vert", DEFAULT_RESOURCE_DIRECTORY + "shaders/default.frag")) {}

	Renderable::Renderable(Shader* shader) : vaoHandle(0), tboHandle(0), vbo(nullptr), ibo(nullptr), numVertices(0), numIndices(0), sizePerVertex(0) {
		this->shader = shader;
	}

	Renderable::~Renderable() {
		delete shader;
		shader = nullptr;

		delete[] vbo;
		vbo = nullptr;

		delete[] ibo;
		ibo = nullptr;
	}

	void Renderable::render(Transform worldTransform, Transform viewProjectionTransform) const {
		// Setup for shader program.
		shader->enable();
		shader->setUniform("world_transform", worldTransform.get_matrix());
		shader->setUniform("inverse_world_transform", worldTransform.get_matrix().inverse());
		shader->setUniform("view_projection_transform", viewProjectionTransform.get_matrix());

		// Draw mesh using its VAO.
		glBindTexture(GL_TEXTURE_2D, tboHandle);
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		shader->disable();
	}
}