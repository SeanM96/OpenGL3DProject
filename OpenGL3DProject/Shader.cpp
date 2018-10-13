#include "Shader.h"
#include "glfw3.h"


Shader::Shader(const GLchar *vs_source, const GLchar *fs_source) {
	myProgram = glCreateProgram();
	if (!myProgram) {
		std::cout << "Error creating shader program!" << "\n";
	}
	else {
		printf("SUCCESFUL SHADER CREATION \n");
	}
	CompileShader(vs_source, fs_source);
}

void Shader::CompileShader(const GLchar *vs_source, const GLchar *fs_source) {
	vertexShader = AddShader(vs_source, GL_VERTEX_SHADER);
	fragmentShader = AddShader(fs_source, GL_FRAGMENT_SHADER);

	glAttachShader(myProgram, vertexShader);
	glAttachShader(myProgram, fragmentShader);

	GLint result = 0;
	GLchar infoLog[1024] = { 0 };

	glLinkProgram(myProgram);
	glGetProgramiv(myProgram, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(myProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error linking program: '%s' \n" << infoLog;
		glfwTerminate();
		return;
	}
	else {
		printf("SUCCESFUL LINKING \n");
	}

	glValidateProgram(myProgram);
	glGetProgramiv(myProgram, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(myProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error validating program: %s \n";
		glfwTerminate();
		return;
	}
	else {
		printf("SUCCESFUL VALIDATION \n");
	}
}

GLuint Shader::AddShader(const std::string shaderCode, GLenum shaderType) {
	GLuint myShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode.c_str();

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode.c_str());

	glShaderSource(myShader, 1, theCode, codeLength);
	glCompileShader(myShader);

	GLint result = 0;
	GLchar infoLog[1024] = { 0 };

	glGetShaderiv(myShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(myShader, sizeof(infoLog), NULL, infoLog);
		printf("Error compiling the %d shader: %s\n", shaderType, infoLog);
		glfwTerminate();
	}
	else {
		printf("SUCCESSFUL SHADER COMPILE \n");
	}
	return myShader;
}


Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(myProgram);
}
