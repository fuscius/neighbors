#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "neighbors.h""

#include <Windows.h>
#include "neighbors.cpp"

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

static game_input GlobalInput;

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
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Neighbors", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, processWindowsCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

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


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}