#include <Windows.h>
#include "neighbors.h"
#include <GLFW/glfw3.h>

void GameUpdateAndRender(GameState *gameState, game_input *input)
{

	if (input->Controller.A.IsDown == true)
	{
		gameState->State = 1;
	}
	if (input->Controller.B.IsDown == true)
	{
		gameState->State = 2;
	}
	if (input->Controller.X.IsDown == true)
	{
		gameState->State = 3;
	}
	if (input->Controller.Y.IsDown == true)
	{
		gameState->State = 0;
	}

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
		OutputDebugStringA("Game should now exit\n");
		break;
	default:
		OutputDebugStringA("Error something is very wrong\n");
		break;
	}
	return;
}