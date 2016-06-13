#if !defined(NEIGHBORS_H)

struct GameState
{
	// Possible states:
	// 0 - Game Exiting
	// 1 - Map View
	// 2 - House View
	// 3 - Score View
	// 
	int State;
};

void GameUpdateAndRender(GameState *gameState, GLFWwindow *window);

#define NEIGHBORS_H
#endif