#pragma once
#include "libs.h"

class Texture
{
public:
	GLuint id;
	GLuint Width, Height;
	GLuint Object_Format, Image_Format;
	GLuint Filter_Min, Filter_Mag;

	GLuint X, Y;
	Texture();
	~Texture();

	void Generate(GLuint width, GLuint height, unsigned char* data, GLuint type);
	void bindTexture(GLint texture_unit, GLenum type);
};

