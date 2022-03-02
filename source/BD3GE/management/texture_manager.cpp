#include "texture_manager.h"

namespace BD3GE {
	std::hash<std::string> TextureManager::string_hasher = std::hash<std::string>();
	std::map<const size_t, Texture*> TextureManager::textures = std::map<const size_t, Texture*>();

	const size_t TextureManager::load_texture(std::string relative_file_path) {
		size_t relative_file_path_hash = get_texture_hash(relative_file_path);
		if (!TextureManager::textures.contains(relative_file_path_hash)) {
			TextureManager::textures[relative_file_path_hash] = new Texture(DEFAULT_TEXTURE_DIRECTORY + relative_file_path);
		}

		return relative_file_path_hash;
	}

	Texture* TextureManager::get_texture(std::string relative_file_path) {
		return get_texture(get_texture_hash(relative_file_path));
	}

	Texture* TextureManager::get_texture(size_t texture_hash) {
		return TextureManager::textures[texture_hash];
	}

	const size_t TextureManager::get_hash(std::string input) {
		return string_hasher(input);
	}

	const size_t TextureManager::get_texture_hash(std::string relative_file_path) {
		return get_hash(relative_file_path);
	}
}