#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glew.h>

class Shader
{
public:
	GLuint myProgram;

	Shader(const GLchar *, const GLchar *);
	~Shader();

private:
	GLuint vertexShader;
	GLuint fragmentShader;

	void CompileShader(const GLchar *, const GLchar *);
	GLuint AddShader(const std::string, GLenum);
};

