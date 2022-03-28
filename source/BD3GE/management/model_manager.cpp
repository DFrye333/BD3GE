#include "model_manager.h"

namespace BD3GE {
	std::hash<std::string> ModelManager::string_hasher = std::hash<std::string>();
	std::map<const size_t, Model*> ModelManager::models = std::map<const size_t, Model*>();

	const size_t ModelManager::load_model(std::string relative_file_path) {
		size_t relative_file_path_hash = get_model_hash(relative_file_path);
		if (!ModelManager::models.contains(relative_file_path_hash)) {
			Model* new_model = new Model(DEFAULT_MODEL_DIRECTORY + relative_file_path);
			new_model->renderable_id = relative_file_path_hash;
			ModelManager::models[relative_file_path_hash] = new_model;
		}

		return relative_file_path_hash;
	}

	Model* ModelManager::get_model(std::string relative_file_path) {
		return get_model(get_model_hash(relative_file_path));
	}

	Model* ModelManager::get_model(size_t texture_hash) {
		return ModelManager::models[texture_hash];
	}

	const size_t ModelManager::get_hash(std::string input) {
		return string_hasher(input);
	}

	const size_t ModelManager::get_model_hash(std::string relative_file_path) {
		return get_hash(relative_file_path);
	}
}