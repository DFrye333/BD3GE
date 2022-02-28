#include "shader_manager.h"

namespace BD3GE {
	std::hash<std::string> ShaderManager::string_hasher = std::hash<std::string>();
	std::map<const size_t, Shader*> ShaderManager::shaders = std::map<const size_t, Shader*>();
	std::map<const size_t, ShaderObject*> ShaderManager::shader_objects = std::map<const size_t, ShaderObject*>();

	const size_t ShaderManager::compile_shader(ShaderManifest shader_manifest) {
		size_t shader_manifest_hash = get_shader_id(shader_manifest);
		if (!shaders.contains(shader_manifest_hash)) {
			size_t vertex_shader_hash = get_hash(shader_manifest.vertex_shader_object);
			size_t fragment_shader_hash = get_hash(shader_manifest.fragment_shader_object);

			if (!shader_objects.contains(vertex_shader_hash)) {
				load_shader_object(GL_VERTEX_SHADER, shader_manifest.vertex_shader_object);
			}
			if (!shader_objects.contains(fragment_shader_hash)) {
				load_shader_object(GL_FRAGMENT_SHADER, shader_manifest.fragment_shader_object);
			}

			shaders[shader_manifest_hash] = new Shader(get_shader_object(vertex_shader_hash), get_shader_object(fragment_shader_hash));
		}

		return shader_manifest_hash;
	}

	Shader* ShaderManager::get_shader(ShaderManifest shader_manifest) {
		const size_t shader_manifest_hash = get_shader_id(shader_manifest);
		return get_shader(shader_manifest_hash);
	}

	Shader* ShaderManager::get_shader(const size_t shader_manifest_hash) {
		return shaders[shader_manifest_hash];
	}

	const size_t ShaderManager::get_shader_id(ShaderManifest shader_manifest) {
		return get_shader_hash(shader_manifest);
	}

	const size_t ShaderManager::load_shader_object(GLenum shader_type, std::string relative_file_path) {
		size_t relative_file_path_hash = get_hash(relative_file_path);
		if (!ShaderManager::shader_objects.contains(relative_file_path_hash)) {
			ShaderManager::shader_objects[relative_file_path_hash] = new ShaderObject(shader_type, DEFAULT_SHADER_DIRECTORY + relative_file_path);
		}

		return relative_file_path_hash;
	}

	void ShaderManager::unload_shader_object(std::string relative_file_path) {
		size_t relative_file_path_hash = get_hash(relative_file_path);
		ShaderObject* shader_object = ShaderManager::shader_objects[relative_file_path_hash];
		glDeleteShader(shader_object->object_ID);
		delete shader_object;
		shader_object = nullptr;
	}

	const ShaderObject* ShaderManager::get_shader_object(std::string relative_file_path) {
		return get_shader_object(get_hash(relative_file_path));
	}

	const ShaderObject* ShaderManager::get_shader_object(size_t relative_file_path_hash) {
		return ShaderManager::shader_objects[relative_file_path_hash];
	}

	const size_t ShaderManager::get_hash(std::string input) {
		return string_hasher(input);
	}

	const size_t ShaderManager::get_shader_hash(ShaderManifest shader_manifest) {
		return get_hash(shader_manifest.vertex_shader_object + "|" + shader_manifest.fragment_shader_object);
	}
}