#ifndef SHADER_H
#define SHADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <glew/GL/glew.h>

#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/matrix.h"
#include "../utility/vector.h"
#include "../video/light.h"

namespace BD3GE {
	class ShaderObject {
		public:
			ShaderObject(GLenum shader_type, std::string shader_source_path);
			void read_file(const std::string file_path, std::string* shader_text);

			GLuint object_ID;
	};

	class Shader {
		public:

					Shader(std::vector<ShaderObject*> shader_objects);
					Shader(ShaderObject* vertex_shader_object, ShaderObject* fragment_shader_object);
					~Shader();
			GLuint	get_program_ID();
			void	enable();
			void	disable();
			void	setUniform(std::string uniform_name, Matrix4 value);
			void	setUniform(std::string uniform_name, Vector3 value);
			void	setUniform(std::string uniform_name, float value);
			void	setUniform(std::string uniform_name, int value);
			void	setUniform(std::string uniform_name, unsigned int value);
			void	setLight(Light* light);

			GLuint program_ID;
			std::map<std::string, std::string> directional_lights;
			std::map<std::string, std::string> point_lights;
			std::map<std::string, std::string> spot_lights;
			unsigned short quantity_directional_lights = 0;
			unsigned short quantity_point_lights = 0;
			unsigned short quantity_spot_lights = 0;
	};
}

#endif // SHADER_H