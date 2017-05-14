#if !defined(SPRITE_SHEET_H)

#include <GL/glew.h>
#include "texture.h"

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class SpriteSheet
{
public:
	Texture2D texture;
	GLfloat* minu;
	GLfloat* maxu;
	GLfloat* minv;
	GLfloat* maxv;
	int currentFrame = 0;

	SpriteSheet();
	// Generates sprite sheet from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	// Binds the sprite sheet as the current active GL_TEXTURE_2D texture object
	void Bind() const;
};
#define SPRITE_SHEET_H
#endif