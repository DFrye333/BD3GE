#include "shader.h"

namespace BD3GE {
	ShaderManifest::ShaderManifest(std::string vertex_shader_object, std::string fragment_shader_object) {
		this->vertex_shader_object = vertex_shader_object;
		this->fragment_shader_object = fragment_shader_object;
	}

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

			g_log.write(Log::TYPE::ERR, "Shader compiler failure in " + std::string(str_shader_type) + " shader:\n " + std::string(information_log_string));
			delete[] information_log_string;
		}
	}

	// Read shader program text from a file.
	void ShaderObject::read_file(const std::string filePath, std::string* shaderText) {
		// Open shader file stream.
		std::ifstream infile(filePath.c_str());

		// Ensure that the shader file was opened successfully.
		if (!infile) {
			g_log.write(Log::TYPE::ERR, "Cannot open shader file path " + filePath + " for reading!");
			return;
		}

		// Read entire file into shader file text string.
		*shaderText = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

		infile.close();
	}

	Shader::Shader(std::vector<const ShaderObject*> shader_objects) {
		compile_shader(shader_objects);
		initialize_shader();
	}

	Shader::Shader(const ShaderObject* vertex_shader_object, const ShaderObject* fragment_shader_object) : Shader(std::vector<const ShaderObject*>{ vertex_shader_object, fragment_shader_object }) {}

	Shader::~Shader() {}

	void Shader::compile_shader(std::vector<const ShaderObject*> shader_objects) {
		this->program_ID = glCreateProgram();

		std::vector<GLuint> shader_object_IDs;
		for (const ShaderObject* shader_object : shader_objects) {
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
			g_log.write(Log::TYPE::ERR, "Shader linker failure: " + std::string(information_log_string));
			delete[] information_log_string;
		}

		for (size_t i = 0; i < shader_object_IDs.size(); ++i) {
			glDetachShader(this->program_ID, shader_object_IDs[i]);
		}
	}

	void Shader::initialize_shader() {}

	GLuint Shader::get_program_ID() {
		return program_ID;
	}

	void Shader::enable() {
		glUseProgram(get_program_ID());
	}

	void Shader::disable() {
		glUseProgram(0);
	}

	void Shader::set_uniform(std::string uniform_name, Matrix4 value) {
		GLfloat transformation_array[16];
		value.to_float_array(transformation_array);
		glProgramUniformMatrix4fv(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, GL_TRUE, transformation_array);
	}

	void Shader::set_uniform(std::string uniform_name, Vector3 value) {
		glProgramUniform3fv(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), 1, value.v.a);
	}

	void Shader::set_uniform(std::string uniform_name, float value) {
		glProgramUniform1f(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::set_uniform(std::string uniform_name, int value) {
		glProgramUniform1i(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::set_uniform(std::string uniform_name, unsigned int value) {
		glProgramUniform1ui(get_program_ID(), glGetUniformLocation(get_program_ID(), uniform_name.c_str()), value);
	}

	void Shader::set_light(Light* light) {
		std::string light_group_name;
		std::string light_index;

		if (light->type == Light::TYPE::DIRECTIONAL) {
			light_group_name = "directional_lights";
			if (directional_lights.contains(light->name)) {
				light_index = directional_lights[light->name];
			}
			else {
				light_index = directional_lights[light->name] = std::to_string(quantity_directional_lights);
				set_uniform("quantity_directional_lights", (unsigned int)(++quantity_directional_lights));
			}

			std::string light_identifier_prefix = light_group_name + "[" + light_index;
			set_uniform(light_identifier_prefix + "].direction", ((DirectionalLight*)light)->direction);
		} else if (light->type == Light::TYPE::POINT) {
			light_group_name = "point_lights";
			if (point_lights.contains(light->name)) {
				light_index = point_lights[light->name];
			} else {
				light_index = point_lights[light->name] = std::to_string(quantity_point_lights);
				set_uniform("quantity_point_lights", (unsigned int)(++quantity_point_lights));
			}

			std::string light_identifier_prefix = light_group_name + "[" + light_index;
			set_uniform(light_identifier_prefix + "].position", ((PointLight*)light)->position);
			set_uniform(light_identifier_prefix + "].attenuation_constant", ((PointLight*)light)->attenuation_constant);
			set_uniform(light_identifier_prefix + "].attenuation_linear", ((PointLight*)light)->attenuation_linear);
			set_uniform(light_identifier_prefix + "].attenuation_quadratic", ((PointLight*)light)->attenuation_quadratic);
		} else if (light->type == Light::TYPE::SPOT) {
			light_group_name = "spot_lights";
			if (spot_lights.contains(light->name)) {
				light_index = spot_lights[light->name];
			}
			else {
				light_index = spot_lights[light->name] = std::to_string(quantity_spot_lights);
				set_uniform("quantity_spot_lights", (unsigned int)(++quantity_spot_lights));
			}

			std::string light_identifier_prefix = light_group_name + "[" + light_index;
			set_uniform(light_identifier_prefix + "].position", ((SpotLight*)light)->position);
			set_uniform(light_identifier_prefix + "].direction", ((SpotLight*)light)->direction);
			set_uniform(light_identifier_prefix + "].inner_cutoff", cos((float)((BD3GE::PI / 180) * ((SpotLight*)light)->inner_cutoff)));
			set_uniform(light_identifier_prefix + "].outer_cutoff", cos((float)((BD3GE::PI / 180) * ((SpotLight*)light)->outer_cutoff)));
		}

		std::string light_identifier_prefix = light_group_name + "[" + light_index;
		set_uniform(light_identifier_prefix + "].is_active", light->is_active);
		set_uniform(light_identifier_prefix + "].color_ambient", light->color_ambient.rgb);
		set_uniform(light_identifier_prefix + "].color_diffuse", light->color_diffuse.rgb);
		set_uniform(light_identifier_prefix + "].color_specular", light->color_specular.rgb);
	}
}