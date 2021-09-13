#include "shader.h"

namespace BD3GE {
	BD3GE::Shader::Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
		programID = create_program(vertexShaderFilePath, fragmentShaderFilePath);
	}

	BD3GE::Shader::~Shader() {}

	// Create a shader program composed of shader objects.
	GLuint BD3GE::Shader::create_program(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
		shaderObjects.push_back(create_shader(GL_VERTEX_SHADER, vertexShaderFilePath));
		shaderObjects.push_back(create_shader(GL_FRAGMENT_SHADER, fragmentShaderFilePath));

		GLuint program_ID = glCreateProgram();

		for (size_t i = 0; i < shaderObjects.size(); ++i) {
			glAttachShader(program_ID, shaderObjects[i]);
		}

		glLinkProgram(program_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(program_ID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint information_log_length;
			glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetProgramInfoLog(program_ID, information_log_length, NULL, information_log_string);
			g_log.write(BD3GE::LOG_TYPE::ERR, "Shader linker failure: " + std::string(information_log_string));
			delete[] information_log_string;
		}

		for (size_t i = 0; i < shaderObjects.size(); ++i) {
			glDetachShader(program_ID, shaderObjects[i]);
		}

		std::for_each(shaderObjects.begin(), shaderObjects.end(), glDeleteShader);

		return program_ID;
	}

	// Create an individual shader object.
	GLuint BD3GE::Shader::create_shader(GLenum shaderType, const std::string filePath) {
		GLuint shader_ID = glCreateShader(shaderType);

		std::string shader_string;
		read_file(filePath, &shader_string);

		const char* shaderText = shader_string.c_str();

		glShaderSource(shader_ID, 1, &shaderText, NULL);

		glCompileShader(shader_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint information_log_length;
			glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetShaderInfoLog(shader_ID, information_log_length, NULL, information_log_string);

			const char* strShaderType = NULL;
			switch (shaderType) {
				case GL_VERTEX_SHADER:
					strShaderType = "vertex";
					break;
				case GL_GEOMETRY_SHADER:
					strShaderType = "geometry";
					break;
				case GL_FRAGMENT_SHADER:
					strShaderType = "fragment";
					break;
			}

			g_log.write(BD3GE::LOG_TYPE::ERR, "Shader compiler failure in " + std::string(strShaderType) + " shader:\n " + std::string(information_log_string));
			delete[] information_log_string;
		}

		return shader_ID;
	}

	// Read shader program text from a file.
	void BD3GE::Shader::read_file(const std::string filePath, std::string* shaderText) {
		// Open shader file stream.
		std::ifstream infile(filePath.c_str());

		// Ensure that the shader file was opened successfully.
		if (!infile) {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Cannot open shader file path " + filePath + " for reading!");
			return;
		}

		// Read entire file into shader file text string.
		*shaderText = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

		infile.close();
	}

	GLuint BD3GE::Shader::get_program_ID() {
		return programID;
	}

	void BD3GE::Shader::enable() {
		glUseProgram(get_program_ID());
	}

	void BD3GE::Shader::disable() {
		glUseProgram(0);
	}

	void BD3GE::Shader::setUniform(std::string uniform_name, Matrix4 matrix) {
		GLfloat transformation_array[16];
		matrix.to_float_array(transformation_array);
		glUniformMatrix4fv(glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, GL_TRUE, transformation_array);
	}

	void BD3GE::Shader::setUniform(std::string uniform_name, Vector3 vector) {
		glUniform3fv(glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, vector.v.a);
	}
}