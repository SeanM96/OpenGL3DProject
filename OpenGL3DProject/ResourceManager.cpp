#include "ResourceManager.h"
#include "libs.h"

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name) {
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name) {
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	for (auto shader : Shaders)
		glDeleteProgram(shader.second.id);
	for (auto texture : Textures)
		glDeleteTextures(1, &texture.second.id);
}

ResourceManager::ResourceManager()
{
}
