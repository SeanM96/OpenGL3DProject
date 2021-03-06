#include "Texture.h"

Texture::Texture(const char* fileName, GLenum type)
{
	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
	glGenTextures(1, &this->id);
	glBindTexture(type, this->id);
	glGenerateMipmap(type);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(type);
		std::cout << "IMAGE LOADED";
	}
	else {
		std::cout << "Error loading image " << fileName;
	}
	//Clean up, needed when stuff done with texture
	glActiveTexture(0);
	glBindTexture(type, 0);
	SOIL_free_image_data(image);
}


Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}

void Texture::bindTexture(GLint texture_unit, GLenum type) {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(type, this->id);
}

void Texture::unbindTexture(GLenum type) {
	glActiveTexture(0);
	glBindTexture(type, 0);
}