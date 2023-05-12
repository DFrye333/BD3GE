#include "material.h"

namespace BD3GE {
	Material::Material() : shader_id(0) {}

	Material::Material(size_t shader_id) : shader_id(shader_id) {}

	Material::Material(size_t shader_id, float gloss_factor) : shader_id(shader_id), gloss_factor(gloss_factor) {}

	SimpleMaterial::SimpleMaterial(size_t shader_id, Color color) : Material(shader_id), color_ambient(color), color_diffuse(color), color_specular(color) {
		this->type = Material::TYPE::SIMPLE;
		this->gamma_diffuse = 1.0f;
		this->gamma_specular = 1.0f;
	}

	SimpleMaterial::SimpleMaterial(size_t shader_id, Color color_ambient, Color color_diffuse, Color color_specular) : Material(shader_id), color_ambient(color_ambient), color_diffuse(color_diffuse), color_specular(color_specular) {
		this->type = Material::TYPE::SIMPLE;
		this->gamma_diffuse = 1.0f;
		this->gamma_specular = 1.0f;
	}

	SimpleMaterial::SimpleMaterial(size_t shader_id, Color color_ambient, Color color_diffuse, Color color_specular, float gloss_factor) : Material(shader_id, gloss_factor), color_ambient(color_ambient), color_diffuse(color_diffuse), color_specular(color_specular) {
		this->type = Material::TYPE::SIMPLE;
		this->gamma_diffuse = 1.0f;
		this->gamma_specular = 1.0f;
	}

	SimpleMaterial::SimpleMaterial(size_t shader_id, aiMaterial* material) : Material(shader_id) {
		this->type = Material::TYPE::SIMPLE;
		this->gamma_diffuse = 1.0f;
		this->gamma_specular = 1.0f;

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
	}

	Material* SimpleMaterial::clone() {
		return new SimpleMaterial(*this);
	}

	void SimpleMaterial::set_color(Color color) {
		this->color_ambient = color;
		this->color_diffuse = color;
		this->color_specular = color;
	}

	MappedMaterial::MappedMaterial() {
		this->type = Material::TYPE::MAPPED;
		this->gamma_diffuse = GAMMA;
		this->gamma_specular = GAMMA;
	}

	MappedMaterial::MappedMaterial(size_t shader_id, size_t map_diffuse_id, size_t map_specular_id, float gloss_factor) : Material(shader_id, gloss_factor), map_diffuse_id(map_diffuse_id), map_specular_id(map_specular_id) {
		this->type = Material::TYPE::MAPPED;
		this->gamma_diffuse = GAMMA;
		this->gamma_specular = GAMMA;
	}

	MappedMaterial::MappedMaterial(size_t shader_id, aiMaterial* material) : Material(shader_id) {
		this->type = Material::TYPE::MAPPED;
		this->gamma_diffuse = GAMMA;
		this->gamma_specular = GAMMA;

		for (unsigned short i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
			aiString texture_file_path;
			material->GetTexture(aiTextureType_DIFFUSE, i, &texture_file_path);
			this->map_diffuse_id = TextureManager::load_texture(std::string(texture_file_path.C_Str()));
		}
		for (unsigned short i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i) {
			aiString texture_file_path;
			material->GetTexture(aiTextureType_SPECULAR, i, &texture_file_path);
			this->map_specular_id = TextureManager::load_texture(std::string(texture_file_path.C_Str()));
		}
	}

	Material* MappedMaterial::clone() {
		return new MappedMaterial(*this);
	}

	CubeMappedMaterial::CubeMappedMaterial() {
		this->type = Material::TYPE::CUBE_MAPPED;
		this->gamma_diffuse = GAMMA;
		this->gamma_specular = GAMMA;
	}

	CubeMappedMaterial::CubeMappedMaterial(size_t shader_id, size_t cubemap_id, CubeMappedMaterial::FACE face) : Material(shader_id), cubemap_id(cubemap_id), face(face) {
		this->type = Material::TYPE::CUBE_MAPPED;
		this->gamma_diffuse = GAMMA;
		this->gamma_specular = GAMMA;
	}

	Material* CubeMappedMaterial::clone() {
		return new CubeMappedMaterial(*this);
	}
}