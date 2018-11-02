#pragma once
#include "libs.h"

class Texture
{

private:
	GLuint id;
	int width, height;
public:
	Texture(const char* fileName, GLenum type);
	~Texture();
	void bindTexture(GLint texture_unit, GLenum type);
	void unbindTexture(GLenum type);
};

