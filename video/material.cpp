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

	SimpleMaterial::SimpleMaterial(Shader* shader, aiMaterial* material) : Material(shader) {
		aiString name;
		float ambient[4];
		float diffuse[4];
		float specular[4];
		material->Get(AI_MATKEY_NAME, name);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient[0]);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse[0]);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular[0]);
		this->color_ambient = Color(Vector3(ambient[0], ambient[1], ambient[2]), ambient[3]);
		this->color_diffuse = Color(Vector3(diffuse[0], diffuse[1], diffuse[2]), diffuse[3]);
		this->color_specular = Color(Vector3(specular[0], specular[1], specular[2]), specular[3]);

		setup();
	}

	void SimpleMaterial::setup() {
		if (this->shader) {
			this->shader->setUniform("is_material_mapped", false);
			this->shader->setUniform("simple_material.color_ambient", this->color_ambient.rgb);
			this->shader->setUniform("simple_material.color_diffuse", this->color_diffuse.rgb);
			this->shader->setUniform("simple_material.color_specular", this->color_specular.rgb);
			this->shader->setUniform("simple_material.gloss_factor", this->gloss_factor);
		}
	}

	void SimpleMaterial::prepForRender() {}

	MappedMaterial::MappedMaterial() : map_diffuse(nullptr), map_specular(nullptr) {}

	MappedMaterial::MappedMaterial(Shader* shader, Texture* map_diffuse, Texture* map_specular, float gloss_factor) : Material(shader, gloss_factor) {
		this->map_diffuse = map_diffuse;
		this->map_specular = map_specular;

		this->shader->setUniform("is_material_mapped", true);
		this->shader->setUniform("mapped_material.map_diffuse", 0);
		this->shader->setUniform("mapped_material.map_specular", 1);
		this->shader->setUniform("mapped_material.gloss_factor", gloss_factor);
	}

	void MappedMaterial::prepForRender() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, map_diffuse->tboHandle);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, map_specular->tboHandle);
	}
}