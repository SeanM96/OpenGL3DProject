#include "Texture.h"

Texture::Texture() : Width(0), Height(0), Object_Format(GL_RGB), Image_Format(GL_RGB), X(GL_REPEAT), Y(GL_REPEAT) {
	glGenTextures(1, &this->id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}

void Texture::Generate(GLuint width, GLuint height, unsigned char* data, GLuint type) {
	this->Width = width;
	this->Height = height;

	glBindTexture(type, this->id);
	glTexImage2D(type, 0, this->Object_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, this->X);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, this->Y);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, this->Filter_Mag);

	glBindTexture(type, 0);
}

void Texture::bindTexture(GLint texture_unit, GLenum type) {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(type, this->id);
}