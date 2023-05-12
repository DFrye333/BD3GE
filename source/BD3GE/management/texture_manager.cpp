#include "texture_manager.h"

namespace BD3GE {
	std::hash<std::string> TextureManager::string_hasher = std::hash<std::string>();
	std::map<const size_t, Texture*> TextureManager::textures = std::map<const size_t, Texture*>();
	std::map<const size_t, size_t[6]> TextureManager::cubemaps = std::map<const size_t, size_t[6]>();

	const size_t TextureManager::load_texture(std::string texture_relative_file_path) {
		std::string config_texture_directory = ConfigManager::get_config_value_string("resource_textures_directory");
		std::string texture_directory = config_texture_directory.size() > 0 ? config_texture_directory : DEFAULT_TEXTURE_DIRECTORY;
		size_t texture_relative_file_path_hash = get_path_hash(texture_relative_file_path);

		if (!TextureManager::textures.contains(texture_relative_file_path_hash)) {
			TextureManager::textures[texture_relative_file_path_hash] = new Texture(texture_directory + texture_relative_file_path);
		}

		return texture_relative_file_path_hash;
	}

	const size_t TextureManager::load_cubemap(std::string cubemap_relative_file_path) {
		size_t cubemap_relative_file_path_hash = get_path_hash(cubemap_relative_file_path);

		if (!TextureManager::cubemaps.contains(cubemap_relative_file_path_hash)) {
			size_t* cubemap_faces = TextureManager::cubemaps[cubemap_relative_file_path_hash];

			// TODO: Handle different file extensions.
			cubemap_faces[0] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "right.jpg");
			cubemap_faces[1] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "left.jpg");
			cubemap_faces[2] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "top.jpg");
			cubemap_faces[3] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "bottom.jpg");
			cubemap_faces[4] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "front.jpg");
			cubemap_faces[5] = TextureManager::load_texture(cubemap_relative_file_path + "/" + "back.jpg");
		}

		return cubemap_relative_file_path_hash;
	}

	Texture* TextureManager::get_texture(std::string texture_relative_file_path) {
		return get_texture(get_path_hash(texture_relative_file_path));
	}

	Texture* TextureManager::get_texture(size_t texture_hash) {
		return TextureManager::textures.contains(texture_hash) ? TextureManager::textures[texture_hash] : nullptr;
	}

	std::vector<Texture*> TextureManager::get_cubemap(std::string cubemap_relative_file_path) {
		return get_cubemap(get_path_hash(cubemap_relative_file_path));
	}

	std::vector<Texture*> TextureManager::get_cubemap(size_t cubemap_hash) {
		if (!TextureManager::cubemaps.contains(cubemap_hash)) { return std::vector<Texture*>(); }

		size_t* cubemap_face_hashes = TextureManager::cubemaps[cubemap_hash];

		std::vector<Texture*> cubemap_face_textures;
		for (unsigned short i = 0; i < 6; ++i) {
			cubemap_face_textures.emplace_back(TextureManager::textures[cubemap_face_hashes[i]]);
		}

		return cubemap_face_textures;
	}

	const size_t TextureManager::get_hash(std::string input) {
		return string_hasher(input);
	}

	const size_t TextureManager::get_path_hash(std::string relative_file_path) {
		return get_hash(relative_file_path);
	}
}