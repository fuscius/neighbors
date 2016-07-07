#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "neighbors.h""
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <Windows.h>

SpriteRenderer  *Renderer;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

static game_input GlobalInput;

// The Width of the screen
const GLuint SCREEN_WIDTH = 1280;
// The height of the screen
const GLuint SCREEN_HEIGHT = 720;

void processWindowsCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	switch (key)
	{
	case GLFW_KEY_A:
	{
		GlobalInput.Controller.Left.IsDown = true;
		break;
	}
	case GLFW_KEY_D:
	{
		GlobalInput.Controller.Right.IsDown = true;
		break;
	}
	case GLFW_KEY_W:
	{
		GlobalInput.Controller.Up.IsDown = true;
		break;
	}
	case GLFW_KEY_S:
	{
		GlobalInput.Controller.Down.IsDown = true;
		break;
	}
	case GLFW_KEY_Q:
	{
		GlobalInput.Controller.L1.IsDown = true;
		break;
	}
	case GLFW_KEY_E:
	{
		GlobalInput.Controller.R1.IsDown = true;
		break;
	}
	case GLFW_KEY_UP:
	{
		GlobalInput.Controller.Y.IsDown = true;
		break;
	}
	case GLFW_KEY_DOWN:
	{
		GlobalInput.Controller.A.IsDown = true;
		break;
	}
	case GLFW_KEY_LEFT:
	{
		GlobalInput.Controller.X.IsDown = true;
		break;
	}
	case GLFW_KEY_RIGHT:
	{
		GlobalInput.Controller.B.IsDown = true;
		break;
	}
	case GLFW_KEY_ESCAPE:
	{
		GlobalInput.Controller.Start.IsDown = true;
		break;
	}
	case GLFW_KEY_SPACE:
	{
		GlobalInput.Controller.Back.IsDown = true;
		break;
	}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neighbors", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE; 

	glewInit();
	glGetError();

	glfwSetKeyCallback(window, processWindowsCallback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // Where in the window to render.
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH),
		static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// Load textures
	ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");

	GameState gameState = {};
	gameState.State = 1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Clear IsDowns to false for incoming input and update WasDown's.
		for (int ButtonIndex = 0; ButtonIndex < ArrayCount(GlobalInput.Controller.Buttons); ButtonIndex++)
		{
			GlobalInput.Controller.Buttons[ButtonIndex].WasDown = GlobalInput.Controller.Buttons[ButtonIndex].IsDown;
			GlobalInput.Controller.Buttons[ButtonIndex].IsDown = false;
		}

		// Controller input handeling.
		if (glfwJoystickPresent(GLFW_JOYSTICK_1))
		{
			int countButtons;
			const unsigned char *button = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &countButtons);
			for (int i = 0; i < countButtons; i++)
			{
				if (button[i] == GLFW_PRESS)
				{
					GlobalInput.Controller.Buttons[i].IsDown = true;
				}
			}

			int countAxes;
			const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &countAxes);
			for (int i = 0; i < countAxes; i++)
			{
				GlobalInput.Controller.Axes[i] = axes[i];
			}
		}

		/* Poll for and process events */
		glfwPollEvents();
		if (gameState.State == 0)
			glfwSetWindowShouldClose(window, 1);
		
		/* Render here */
		GameUpdateAndRender(&gameState, &GlobalInput);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer->DrawSprite(ResourceManager::GetTexture("face"),
			glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}