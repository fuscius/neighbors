#include <iostream>

#include "spriteSheet.h"


SpriteSheet::SpriteSheet()
	: texture()
{
	glGenTextures(1, &this->texture.ID);
}

void SpriteSheet::Generate(GLuint width, GLuint height, unsigned char* data)
{
	this->texture.Width = width;
	this->texture.Height = height;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->texture.ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->texture.Internal_Format, width, height, 0, this->texture.Image_Format, GL_UNSIGNED_BYTE, data);
	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->texture.Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->texture.Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->texture.Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->texture.Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteSheet::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->texture.ID);
}