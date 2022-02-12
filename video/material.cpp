#include "material.h"

namespace BD3GE {
	Material::Material() : shader(nullptr) {}

	Material::Material(Shader* shader) : shader(shader) {}

	Material::Material(Shader* shader, int gloss_factor) : shader(shader), gloss_factor(gloss_factor) {}

	Material::~Material() {
		delete shader;
		shader = nullptr;
	}

	SimpleMaterial::SimpleMaterial(Shader* shader, Color color) : Material(shader), color_ambient(color), color_diffuse(color), color_specular(color) {
		setup();
	}

	SimpleMaterial::SimpleMaterial(Shader* shader, Color color_ambient, Color color_diffuse, Color color_specular) : Material(shader), color_ambient(color_ambient), color_diffuse(color_diffuse), color_specular(color_specular) {
		setup();
	}

	SimpleMaterial::SimpleMaterial(Shader* shader, Color color_ambient, Color color_diffuse, Color color_specular, float gloss_factor) : Material(shader, gloss_factor), color_ambient(color_ambient), color_diffuse(color_diffuse), color_specular(color_specular) {
		setup();
	}

	void SimpleMaterial::setup() {
		if (this->shader) {
			this->shader->setUniform("material.color_ambient", this->color_ambient.rgb);
			this->shader->setUniform("material.color_diffuse", this->color_diffuse.rgb);
			this->shader->setUniform("material.color_specular", this->color_specular.rgb);
			this->shader->setUniform("material.gloss_factor", this->gloss_factor);
		}
	}

	void SimpleMaterial::prepForRender() {}

	MappedMaterial::MappedMaterial() : map_diffuse(nullptr), map_specular(nullptr) {}

	MappedMaterial::MappedMaterial(Shader* shader, Texture* map_diffuse, Texture* map_specular, float gloss_factor) : Material(shader, gloss_factor) {
		this->map_diffuse = map_diffuse;
		this->map_specular = map_specular;

		this->shader->setUniform("material.map_diffuse", 0);
		this->shader->setUniform("material.map_specular", 1);
		this->shader->setUniform("material.gloss_factor", gloss_factor);
	}

	void MappedMaterial::prepForRender() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, map_diffuse->tboHandle);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, map_specular->tboHandle);
	}
}