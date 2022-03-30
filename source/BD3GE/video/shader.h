#ifndef BD3GE_SHADER_H
#define BD3GE_SHADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <glew/GL/glew.h>

#include "../system/api.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/log.h"
#include "../utility/matrix.h"
#include "../utility/vector.h"
#include "../video/light.h"

namespace BD3GE {
	class BD3GE_API ShaderManifest {
		public:
			ShaderManifest(std::string vertex_shader_object, std::string fragment_shader_object);

			std::string vertex_shader_object;
			std::string fragment_shader_object;
	};

	class ShaderObject {
		public:
			ShaderObject(GLenum shader_type, std::string shader_source_path);
			void read_file(const std::string file_path, std::string* shader_text);

			GLuint object_ID;
			bool has_compiled_successfully = false;
	};

	class Shader {
		public:
					Shader(std::vector<const ShaderObject*> shader_objects);
					Shader(const ShaderObject* vertex_shader_object, const ShaderObject* fragment_shader_object);
					~Shader();
			void	compile_shader(std::vector<const ShaderObject*> shader_objects);
			void	initialize_shader();
			GLuint	get_program_ID();
			void	enable();
			void	disable();
			void	set_uniform(std::string uniform_name, Matrix4 value);
			void	set_uniform(std::string uniform_name, Vector3 value);
			void	set_uniform(std::string uniform_name, float value);
			void	set_uniform(std::string uniform_name, int value);
			void	set_uniform(std::string uniform_name, unsigned int value);
			void	set_light(Light* light);

			GLuint program_ID;
			GLuint ubo_handle;
			std::map<std::string, std::string> directional_lights;
			std::map<std::string, std::string> point_lights;
			std::map<std::string, std::string> spot_lights;
			unsigned short quantity_directional_lights = 0;
			unsigned short quantity_point_lights = 0;
			unsigned short quantity_spot_lights = 0;
	};
}

#endif // BD3GE_SHADER_H