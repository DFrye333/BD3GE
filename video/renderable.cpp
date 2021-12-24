#include "renderable.h"

namespace BD3GE {
	Renderable::Renderable() : Renderable(new Shader(), new SimpleMaterial()) {
		this->owns_shader = true;
		this->owns_simple_material = true;
		this->owns_mapped_material = true;
	}

	Renderable::Renderable(Shader* shader) : Renderable(shader, new SimpleMaterial()) {
		this->owns_shader = false;
		this->owns_simple_material = true;
		this->owns_mapped_material = true;
	}

	Renderable::Renderable(SimpleMaterial* simpleMaterial) : Renderable(new Shader(), simpleMaterial) {
		this->owns_shader = true;
		this->owns_simple_material = false;
		this->owns_mapped_material = true;
	}

	Renderable::Renderable(Shader* shader, SimpleMaterial* simpleMaterial) : shader(shader), simpleMaterial(simpleMaterial), mappedMaterial(nullptr), owns_shader(false), owns_simple_material(false), owns_mapped_material(true), vaoHandle(0), vbo(nullptr), ibo(nullptr), numVertices(0), numIndices(0), sizePerVertex(0) {
		setMaterial(simpleMaterial);
	}

	Renderable::Renderable(Shader* shader, MappedMaterial* mappedMaterial) : shader(shader), simpleMaterial(nullptr), mappedMaterial(mappedMaterial), owns_shader(false), owns_simple_material(true), owns_mapped_material(false), vaoHandle(0), vbo(nullptr), ibo(nullptr), numVertices(0), numIndices(0), sizePerVertex(0) {
		setMaterial(mappedMaterial);
	}

	Renderable::~Renderable() {
		if (owns_shader) {
			delete shader;
			shader = nullptr;
		}

		if (owns_simple_material) {
			delete simpleMaterial;
			simpleMaterial = nullptr;
		}

		if (owns_mapped_material) {
			delete mappedMaterial;
			mappedMaterial = nullptr;
		}

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

	void Renderable::render(Transform worldTransform, Transform viewProjectionTransform) const {
		// Setup for shader program.
		shader->enable();

		shader->setUniform("world_transform", worldTransform.get_matrix());
		shader->setUniform("inverse_world_transform", worldTransform.get_matrix().inverse());
		shader->setUniform("view_projection_transform", viewProjectionTransform.get_matrix());

		// Draw mesh using its VAO.
		for (int i = 0; i < tboHandles.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, tboHandles[i]);
		}
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Cleanup.
		shader->disable();
	}

	void Renderable::addTexture(int textureId, Texture* texture) {
		if (texture != nullptr && texture->data != nullptr) {
			GLuint tboHandle;
			glGenTextures(1, &tboHandle);
			tboHandles.push_back(tboHandle);

			glActiveTexture(GL_TEXTURE0 + textureId);
			glBindTexture(GL_TEXTURE_2D, tboHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			GLint format;
			switch (texture->quantityChannels) {
				case 1: format = GL_RED; break;
				case 3: format = GL_RGB; break;
				case 4: format = GL_RGBA; break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	void Renderable::setMaterial(SimpleMaterial* simpleMaterial) {
		this->simpleMaterial = simpleMaterial;

		shader->setUniform("material.color_ambient", simpleMaterial->color_ambient);
		shader->setUniform("material.color_diffuse", simpleMaterial->color_diffuse);
		shader->setUniform("material.color_specular", simpleMaterial->color_specular);
		shader->setUniform("material.gloss_factor", simpleMaterial->gloss_factor);
	}

	void Renderable::setMaterial(MappedMaterial* mappedMaterial) {
		this->mappedMaterial = mappedMaterial;

		addTexture(0, mappedMaterial->map_diffuse);
		shader->setUniform("material.map_diffuse", 0);

		addTexture(1, mappedMaterial->map_specular);
		shader->setUniform("material.map_specular", 1);

		shader->setUniform("material.gloss_factor", mappedMaterial->gloss_factor);
	}
}