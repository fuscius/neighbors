#include "neighbors.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

void GameUpdateAndRender(GameState *gameState, game_input *input)
{
	if (input->Controller.Up.IsDown == true)
	{
		gameState->PlayerY -= 30;
	}
	if (input->Controller.Down.IsDown == true)
	{
		gameState->PlayerY += 30;
	}
	if (input->Controller.Left.IsDown == true)
	{
		gameState->PlayerX -= 30;
	}
	if (input->Controller.Right.IsDown == true)
	{
		gameState->PlayerX += 30;
	}
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
		//OutputDebugStringA("We are currently on the Map View\n");
		break;
	case 2:
		//OutputDebugStringA("We are currently on the House View\n");
		break;
	case 3:
		//OutputDebugStringA("We are currently on the Score View\n");
		break;
	case 0:
		//OutputDebugStringA("Game should now exit\n");
		break;
	default:
		//OutputDebugStringA("Error something is very wrong\n");
		break;
	}
	return;
}