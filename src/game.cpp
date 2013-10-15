#include "game.h"
#include "input.h"
#include <stdio.h>


static void Game_HandleInput()
{
	InputEvent event;

	while ( Input_PopEvent( &event ) )
	{
		printf( "Input Event: %d %d\n", event.type, event.key );
	}
}


void Game_Initialize()
{
}


void Game_Shutdown()
{
}


void Game_Frame()
{
	Game_HandleInput();
}
