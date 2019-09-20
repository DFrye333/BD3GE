#include "shader.h"

namespace BD3GE
{
	/*
	 * 	Shader class
	 */

	BD3GE::Shader::Shader()
	{
		m_program_ID = create_program();
	}

	BD3GE::Shader::~Shader()
	{
	}

	// Create a shader program composed of shader objects.
	GLuint BD3GE::Shader::create_program(void)
	{
		m_shader_objects.push_back(create_shader(GL_VERTEX_SHADER, "resource/shader/vertex.glsl"));
		m_shader_objects.push_back(create_shader(GL_FRAGMENT_SHADER, "resource/shader/fragment.glsl"));

		GLuint program_ID = glCreateProgram();

		for (size_t i = 0; i < m_shader_objects.size(); ++i)
		{
			glAttachShader(program_ID, m_shader_objects[i]);
		}

		glLinkProgram(program_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(program_ID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint information_log_length;
			glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetProgramInfoLog(program_ID, information_log_length, NULL, information_log_string);
			g_log.write(BD3GE::LOG_TYPE::ERR, "Shader linker failure: " + std::string(information_log_string));
			delete[] information_log_string;
		}

		for (size_t i = 0; i < m_shader_objects.size(); ++i)
		{
			glDetachShader(program_ID, m_shader_objects[i]);
		}

		std::for_each(m_shader_objects.begin(), m_shader_objects.end(), glDeleteShader);

		return program_ID;
	}

	// Create an individual shader object.
	GLuint BD3GE::Shader::create_shader(GLenum shaderType, const std::string filePath)
	{
		GLuint shader_ID = glCreateShader(shaderType);

		std::string shader_string;
		read_file(filePath, &shader_string);

		const char* shaderText = shader_string.c_str();

		glShaderSource(shader_ID, 1, &shaderText, NULL);

		glCompileShader(shader_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint information_log_length;
			glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetShaderInfoLog(shader_ID, information_log_length, NULL, information_log_string);

			const char* strShaderType = NULL;
			switch (shaderType)
			{
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
	void BD3GE::Shader::read_file(const std::string filePath, std::string* shaderText)
	{
		// Open shader file stream.
		std::ifstream infile(filePath.c_str());

		// Ensure that the shader file was opened successfully.
		if (!infile)
		{
			g_log.write(BD3GE::LOG_TYPE::ERR, "Cannot open shader file path " + filePath + " for reading!");
			return;
		}

		// Read entire file into shader file text string.
		*shaderText = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

		infile.close();
	}

	GLuint BD3GE::Shader::get_program_ID(void)
	{
		return m_program_ID;
	}
}