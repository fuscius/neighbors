#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, SpriteSheet>  ResourceManager::SpriteSheets;


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

SpriteSheet ResourceManager::LoadSpriteSheet(const GLchar *file, GLboolean alpha, std::string name)
{
	SpriteSheets[name] = loadSpriteSheetFromFIle(file, alpha);
	return SpriteSheets[name];
}

SpriteSheet ResourceManager::GetSpriteSheet(std::string name)
{
	return SpriteSheets[name];
}

//void ResourceManager::Clear()
//{
//	// (Properly) delete all shaders	
//	for (auto iter : Shaders)
//		glDeleteProgram(iter.second.ID);
//	// (Properly) delete all textures
//	for (auto iter : Textures)
//		glDeleteTextures(1, &iter.second.ID);
//}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}

SpriteSheet ResourceManager::loadSpriteSheetFromFIle(const GLchar *file, GLboolean alpha)
{
	SpriteSheet sheet;
	if (alpha)
	{
		sheet.texture.Internal_Format = GL_RGBA;
		sheet.texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, sheet.texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	sheet.texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);

	sheet.currentFrame = 0;
	sheet.maxu = new GLfloat[6];
	sheet.minu = new GLfloat[6];
	sheet.maxv = new GLfloat[6];
	sheet.minv = new GLfloat[6];
	
//	sheet.minu[0] = 0.0f;
//	sheet.maxu[0] = 29.0f / width;
//	sheet.minv[0] = 45.0f / height;
//	sheet.maxv[0] = 86.0f / height;

//	sheet.minu[1] = 29.0f / width;
//	sheet.maxu[1] = 56.0f / width;
//	sheet.minv[1] = 45.0f / height;
//	sheet.maxv[1] = 86.0f / height;

	sheet.minu[0] = 0.0f;
	sheet.maxu[0] = 32.0f / width;
	sheet.minv[0] = 247.0f / height;
	sheet.maxv[0] = 283.0f / height;

	sheet.minu[1] = 34.0f / width;
	sheet.maxu[1] = 66.0f / width;
	sheet.minv[1] = 247.0f / height;
	sheet.maxv[1] = 283.0f / height;

	sheet.minu[2] = 73.0f / width;
	sheet.maxu[2] = 105.0f / width;
	sheet.minv[2] = 247.0f / height;
	sheet.maxv[2] = 283.0f / height;

	sheet.minu[3] = 110.0f / width;
	sheet.maxu[3] = 142.0f / width;
	sheet.minv[3] = 247.0f / height;
	sheet.maxv[3] = 283.0f / height;

	sheet.minu[4] = 148.0f / width;
	sheet.maxu[4] = 180.0f / width;
	sheet.minv[4] = 247.0f / height;
	sheet.maxv[4] = 283.0f / height;

	sheet.minu[5] = 185.0f / width;
	sheet.maxu[5] = 217.0f / width;
	sheet.minv[5] = 247.0f / height;
	sheet.maxv[5] = 283.0f / height;

	return sheet;
}