#ifndef BD3GE_SHADER_MANAGER_H
#define BD3GE_SHADER_MANAGER_H

#include <map>
#include <string>

#include <glew/GL/glew.h>

#include "../system/constants.h"
#include "../video/shader.h"

namespace BD3GE {
	class ShaderManager {
		public:
			static const size_t compile_shader(ShaderManifest shader_manifest);
			static Shader* get_shader(ShaderManifest shader_manifest);
			static Shader* get_shader(const size_t shader_manifest_hash);
			static const size_t get_shader_id(ShaderManifest shader_manifest);

		private:
			static const size_t load_shader_object(GLenum shader_type, std::string relative_file_path);
			static void unload_shader_object(std::string relative_file_path);
			static const ShaderObject* get_shader_object(std::string relative_file_path);
			static const ShaderObject* get_shader_object(const size_t relative_file_path_hash);
			static const size_t get_hash(std::string input);
			static const size_t get_shader_hash(ShaderManifest shader_manifest);

			static std::hash<std::string> string_hasher;
			static std::map<const size_t, Shader*> shaders;
			static std::map<const size_t, ShaderObject*> shader_objects;
	};
}

#endif // BD3GE_SHADER_MANAGER_H