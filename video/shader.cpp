#include "shader.h"

namespace BD3GE {
	ShaderObject::ShaderObject(GLenum shader_type, std::string shader_source_path) {
		this->object_ID = glCreateShader(shader_type);

		std::string shader_string;
		read_file(shader_source_path, &shader_string);

		const char* shaderText = shader_string.c_str();
		glShaderSource(object_ID, 1, &shaderText, NULL);
		glCompileShader(object_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(object_ID, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint information_log_length;
			glGetShaderiv(object_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetShaderInfoLog(object_ID, information_log_length, NULL, information_log_string);

			const char* str_shader_type = nullptr;
			switch (shader_type) {
				case GL_VERTEX_SHADER: str_shader_type = "vertex"; break;
				case GL_GEOMETRY_SHADER: str_shader_type = "geometry"; break;
				case GL_FRAGMENT_SHADER: str_shader_type = "fragment"; break;
			}

			g_log.write(LOG_TYPE::ERR, "Shader compiler failure in " + std::string(str_shader_type) + " shader:\n " + std::string(information_log_string));
			delete[] information_log_string;
		}
	}

	// Read shader program text from a file.
	void ShaderObject::read_file(const std::string filePath, std::string* shaderText) {
		// Open shader file stream.
		std::ifstream infile(filePath.c_str());

		// Ensure that the shader file was opened successfully.
		if (!infile) {
			g_log.write(LOG_TYPE::ERR, "Cannot open shader file path " + filePath + " for reading!");
			return;
		}

		// Read entire file into shader file text string.
		*shaderText = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

		infile.close();
	}

	Shader::Shader(std::vector<ShaderObject*> shader_objects) {
		this->program_ID = glCreateProgram();

		std::vector<GLuint> shader_object_IDs;
		for (ShaderObject* shader_object : shader_objects) {
			shader_object_IDs.push_back(shader_object->object_ID);
		}

		for (size_t i = 0; i < shader_object_IDs.size(); ++i) {
			glAttachShader(this->program_ID, shader_object_IDs[i]);
		}

		glLinkProgram(this->program_ID);

		GLint status = GL_TRUE;
		glGetShaderiv(this->program_ID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint information_log_length;
			glGetProgramiv(this->program_ID, GL_INFO_LOG_LENGTH, &information_log_length);

			GLchar* information_log_string = new GLchar[information_log_length + 1];
			glGetProgramInfoLog(this->program_ID, information_log_length, NULL, information_log_string);
			g_log.write(LOG_TYPE::ERR, "Shader linker failure: " + std::string(information_log_string));
			delete[] information_log_string;
		}

		for (size_t i = 0; i < shader_object_IDs.size(); ++i) {
			glDetachShader(this->program_ID, shader_object_IDs[i]);
		}

		// TODO: Move the deletion/cleanup logic into a shader management class.
		//std::for_each(shader_object_IDs.begin(), shader_object_IDs.end(), glDeleteShader);
	}

	Shader::Shader(ShaderObject* vertex_shader_object, ShaderObject* fragment_shader_object) : Shader(std::vector<ShaderObject*>{ vertex_shader_object, fragment_shader_object }) {}

	Shader::~Shader() {}

	GLuint Shader::get_program_ID() {
		return program_ID;
	}

	void Shader::enable() {
		glUseProgram(get_program_ID());
	}

	void Shader::disable() {
		glUseProgram(0);
	}

	void Shader::setUniform(std::string uniform_name, Matrix4 value) {
		GLfloat transformation_array[16];
		value.to_float_array(transformation_array);
		glProgramUniformMatrix4fv(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, GL_TRUE, transformation_array);
	}

	void Shader::setUniform(std::string uniform_name, Vector3 value) {
		glProgramUniform3fv(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, value.v.a);
	}

	void Shader::setUniform(std::string uniform_name, float value) {
		glProgramUniform1f(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::setUniform(std::string uniform_name, int value) {
		glProgramUniform1i(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::setUniform(std::string uniform_name, unsigned int value) {
		glProgramUniform1ui(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::setLight(Light* light) {
		std::string light_index;
		if (lights.contains(light->name)) {
			light_index = lights[light->name];
		} else {
			light_index = lights[light->name] = std::to_string(quantity_lights);
			setUniform("quantity_lights", (unsigned int)(++quantity_lights));
		}

		setUniform("lights[" + light_index + "].position", light->position);
		setUniform("lights[" + light_index + "].color_ambient", light->color_ambient.rgb);
		setUniform("lights[" + light_index + "].color_diffuse", light->color_diffuse.rgb);
		setUniform("lights[" + light_index + "].color_specular", light->color_specular.rgb);
		setUniform("lights[" + light_index + "].attenuation_constant", light->attenuation_constant);
		setUniform("lights[" + light_index + "].attenuation_linear", light->attenuation_linear);
		setUniform("lights[" + light_index + "].attenuation_quadratic", light->attenuation_quadratic);
	}
}