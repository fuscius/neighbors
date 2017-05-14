#ifndef ANIMATED_SPRITE_RENDERER_H
#define ANIMATED_SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "spriteSheet.h"
#include "shader.h"


class AnimatedSpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	AnimatedSpriteRenderer(Shader &shader);
	// Destructor
	~AnimatedSpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(SpriteSheet &sheet, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), int frame = 0);
private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif