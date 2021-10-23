#include "renderable.h"

namespace BD3GE {
	Renderable::Renderable() : Renderable(new Shader(), new Material()) {
		this->owns_shader = true;
		this->owns_material = true;
	}

	Renderable::Renderable(Shader* shader) : Renderable(shader, new Material()) {
		this->owns_shader = false;
		this->owns_material = true;
	}

	Renderable::Renderable(Material* material) : Renderable(new Shader(), material) {
		this->owns_shader = true;
		this->owns_material = false;
	}

	Renderable::Renderable(Shader* shader, Material* material) : shader(shader), material(material), owns_shader(false), owns_material(false), vaoHandle(0), tboHandle(0), vbo(nullptr), ibo(nullptr), numVertices(0), numIndices(0), sizePerVertex(0) {
		shader->addMaterial(Material(*material));
	}

	Renderable::~Renderable() {
		if (owns_shader) {
			delete shader;
			shader = nullptr;
		}

		if (owns_material) {
			delete material;
			material = nullptr;
		}

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