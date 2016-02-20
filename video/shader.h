#ifndef SHADER_H
#define SHADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "../system/constants.h"
#include "../system/globals.h"

namespace BD3GE
{
	class Shader
	{
		public:

					Shader();
					~Shader();
			GLuint	get_program_ID(void);

		private:

			GLuint		create_program(void);
			GLuint		create_shader(GLenum shader_type, const std::string file_path);
			void		read_file(const std::string file_path, std::string* shader_text);

			std::vector<GLuint>		m_shader_objects;
			GLuint					m_program_ID;
	};
}

#endif // SHADER_H
