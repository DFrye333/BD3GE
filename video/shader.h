#ifndef SHADER_H
#define SHADER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "../system/constants.h"

class Shader
{
	public:

				Shader();
				~Shader();
		GLuint	getProgramId(void);

	private:

		GLuint		createProgram(void);
		GLuint		createShader(GLenum shaderType, const std::string filePath);
		void		readFile(const std::string filePath, std::string* shaderText);

		std::vector<GLuint>		mShaderObjects;
		GLuint					mProgramId;
};

#endif // SHADER_H
