#pragma once
#include "Texture.h"
#include "Shader.h"
#include "libs.h"

#include <map>
#include <string>

class ResourceManager
{
public:
	//Used for storing shaders and textures
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;
	
	//Loads shader, generates shader
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);
	//Gets Shader by name
	static Shader GetShader(std::string name);

	//Loads and generates texture
	static Texture LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture GetTexture(std::string name);

	//Clears all current textures and shaders
	static void Clear();

private:
	//Private because don't actually want any resource manager objects, it's basically just a middle man. Everything that matters is public
	ResourceManager() {}
	//From file
	static Shader loadShaderFromFile(const GLchar *vshaderFile, const GLchar *fshaderFile);
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

