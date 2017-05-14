#include "neighbors.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "windows-neighbors.h"

void GameUpdateAndRender(GameState *gameState, game_input *input, RenderList *renderList)
{
	if (input->Controller.Up.IsDown == true)
	{
		gameState->RenderState++;
		if (gameState->RenderState > 5)
			gameState->RenderState = 0;
//		gameState->PlayerY -= 20;
	}
	if (input->Controller.Down.IsDown == true)
	{
		gameState->RenderState--;
		if (gameState->RenderState < 0)
			gameState->RenderState = 5;
//		gameState->PlayerY += 20;
	}
	if (input->Controller.Left.IsDown == true)
	{
		gameState->PlayerX -= 20;
	}
	if (input->Controller.Right.IsDown == true)
	{
		gameState->PlayerX += 20;
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
/*
	RenderObject *Player;
	Player = new RenderObject[2];
	Player[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	Player[0].name = "face";
	Player[0].position = glm::vec2(gameState->PlayerX, gameState->PlayerY);
	Player[0].scale = glm::vec2(169 / 2, 297 / 2);

	Player[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
	Player[1].name = "other";
	Player[1].position = glm::vec2(10, 10);
	Player[1].scale = glm::vec2(200, 200);

	renderList->frontList = Player;
*/

	char *name = "face";
	RenderObject * Player = new RenderObject;
	Player->color = glm::vec3(1.0f, 1.0f, 1.0f);
	Player->name = name;
	Player->position = glm::vec2(gameState->PlayerX, gameState->PlayerY);
	Player->scale = glm::vec2(169 / 2, 297 / 2);
	renderList->Push(Player);

	RenderObject * Floor = new RenderObject;
	Floor->color = glm::vec3(1.0f, 1.0f, 1.0f);
	Floor->name = "floor";
	Floor->position = glm::vec2(0, 500);
	Floor->scale = glm::vec2(1241, 200);
	renderList->Push(Floor);

	RenderObject * BackWall = new RenderObject;
	BackWall->color = glm::vec3(1.0f, 1.0f, 1.0f);
	BackWall->name = "backwall";
	BackWall->position = glm::vec2(0, 150);
	BackWall->scale = glm::vec2(1091, 375);
	renderList->Push(BackWall);



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