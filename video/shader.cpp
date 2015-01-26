#include "shader.h"

/*
 * 	Shader class
 */

Shader::Shader()
{
	mProgramId = createProgram();
}

Shader::~Shader()
{
}

// Create a shader program composed of shader objects.
GLuint Shader::createProgram(void)
{
	mShaderObjects.push_back(createShader(GL_VERTEX_SHADER, "/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/vertex.glsl"));
	mShaderObjects.push_back(createShader(GL_FRAGMENT_SHADER, "/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/fragment.glsl"));

	GLuint programId = glCreateProgram();

	for (size_t i = 0; i < mShaderObjects.size(); ++i)
	{
		glAttachShader(programId, mShaderObjects[i]);
	}

	glLinkProgram(programId);

	GLint status;
	glGetShaderiv(programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programId, infoLogLength, NULL, strInfoLog);
		std::cerr << BD3GE_PRINT_ERROR << "Shader linker failure: " << strInfoLog << std::endl;
		delete[] strInfoLog;
	}

	for (size_t i = 0; i < mShaderObjects.size(); ++i)
	{
		glDetachShader(programId, mShaderObjects[i]);
	}

	std::for_each(mShaderObjects.begin(), mShaderObjects.end(), glDeleteShader);

	return programId;
}

// Create an individual shader object.
GLuint Shader::createShader(GLenum shaderType, const std::string filePath)
{
	GLuint shaderId = glCreateShader(shaderType);

	std::string shaderString;
	readFile(filePath, &shaderString);

	const char* shaderText = shaderString.c_str();

	glShaderSource(shaderId, 1, &shaderText, NULL);

	glCompileShader(shaderId);

	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);

		const char* strShaderType = NULL;
		switch(shaderType)
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

		std::cerr << BD3GE_PRINT_ERROR << "Shader compiler failure in " << strShaderType << " shader:\n " << strInfoLog << std::endl;
		delete[] strInfoLog;
	}

	return shaderId;
}

// Read shader program text from a file.
void Shader::readFile(const std::string filePath, std::string* shaderText)
{
	// Open shader file stream.
	std::ifstream infile(filePath.c_str());

	// Ensure that the shader file was opened successfully.
	if (infile == NULL)
	{
		std::cerr << "(BD3GE | Error): Cannot open shader file path " << filePath << " for reading!" << std::endl;
		return;
	}

	// Read entire file into shader file text string.
	*shaderText = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

	infile.close();
}

GLuint Shader::getProgramId(void)
{
	return mProgramId;
}
