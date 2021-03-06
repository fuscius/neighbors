#if !defined(NEIGHBORS_H)

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "windows-neighbors.h"

struct GameState
{
	// Possible states:
	// 0 - Game Exiting
	// 1 - Map View
	// 2 - House View
	// 3 - Score View
	// 
	int State;
	double PlayerX;
	double PlayerY;

	int RenderState;

	// The Width of the screen
	const int ScreenWidth = 1280;
	// The height of the screen
	const int ScreenHeight = 720;
};

struct game_button_state
{
	bool IsDown;
	bool WasDown;
};

struct game_controller_input
{
	bool IsConnected;

	union
	{
		float Axes[6];
		struct
		{
			float LeftStickX;
			float LeftStickY;
			float RightStickX;
			float RightStickY;
			float R2;
			float L2;
		};
	};

	// button order matters as we are mapping the values 
	// directly from GLFW into our keyboard object.
	union
	{
		game_button_state Buttons[14];
		struct
		{
			game_button_state A;
			game_button_state B;
			game_button_state X;
			game_button_state Y;
			
			game_button_state L1;
			game_button_state R1;

			game_button_state Back;
			game_button_state Start;

			game_button_state L3;
			game_button_state R3;

			game_button_state Up;
			game_button_state Right;
			game_button_state Down;
			game_button_state Left;
		};
	};
};

struct game_input
{
	game_controller_input Controller;
};

void GameUpdateAndRender(GameState *gameState, game_input *input, RenderList *renderList);

#define NEIGHBORS_H
#endif