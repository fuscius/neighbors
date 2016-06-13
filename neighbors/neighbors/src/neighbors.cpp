#include <Windows.h>
#include "neighbors.h"
#include <GLFW/glfw3.h>

void GameUpdateAndRender(GameState *gameState, GLFWwindow* window)
{
	

	switch (gameState->State)
	{
	case 1:
		OutputDebugStringA("We are currently on the Map View\n");
		break;
	case 2:
		OutputDebugStringA("We are currently on the House View\n");
		break;
	case 3:
		OutputDebugStringA("We are currently on the Score View\n");
		break;
	case 0:
		glfwSetWindowShouldClose(window, 1);
		OutputDebugStringA("Game should now exit\n");
		break;
	default:
		OutputDebugStringA("Error something is very wrong\n");
		break;
	}
	return;
}