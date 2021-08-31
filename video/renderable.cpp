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

	void Renderable::render(Transform worldTransform, Transform viewProjectionTransform) {
		// Setup for shader program.
		glUseProgram(shader->get_program_ID());

		GLfloat transformation_array[16];
		worldTransform.to_float_array(transformation_array);
		glUniformMatrix4fv(glGetUniformLocation(shader->get_program_ID(), "world_transform"), 1, GL_TRUE, transformation_array);
		viewProjectionTransform.to_float_array(transformation_array);
		glUniformMatrix4fv(glGetUniformLocation(shader->get_program_ID(), "view_projection_transform"), 1, GL_TRUE, transformation_array);

		// Draw mesh using its VAO.
		glBindTexture(GL_TEXTURE_2D, tboHandle);
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		glUseProgram(0);
	}
}