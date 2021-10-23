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
#include "../video/material.h"

namespace BD3GE {
	class Shader {
		public:

					Shader();
					Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);
					~Shader();
			GLuint	get_program_ID();
			void	enable();
			void	disable();
			void	setUniform(std::string uniform_name, Matrix4 value);
			void	setUniform(std::string uniform_name, Vector3 value);
			void	setUniform(std::string uniform_name, float value);
			void	addLight(Light light);
			void	addMaterial(Material material);

		private:

			GLuint		create_program(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);
			GLuint		create_shader(GLenum shader_type, const std::string file_path);
			void		read_file(const std::string file_path, std::string* shader_text);

			GLuint					programID;
			std::vector<GLuint>		shaderObjects;
			std::vector<Light*>		lights;
			std::vector<Material*>	materials;
	};
}

#endif // SHADER_H