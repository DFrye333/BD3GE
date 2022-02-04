#ifndef SHADER_H
#define SHADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

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

					Shader();
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
			void	addLight(Light light);

			GLuint							program_ID;
			std::vector<Light*>				lights;
	};
}

#endif // SHADER_H