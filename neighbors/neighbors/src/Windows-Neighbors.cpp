#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>
#include "neighbors.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GameState gameState = {};
	gameState.State = 1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GameUpdateAndRender(&gameState, window);
		
		// Loop though the different states and then close.
		// Once we add input processing we can chang this to
		// be changed via a button press.
		gameState.State++;
		if (gameState.State > 3)
			gameState.State = 0;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}