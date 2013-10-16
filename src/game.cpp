#include "game.h"
#include "input.h"
#include <stdio.h>
#include <memory.h>
#include <math.h>
#define PI (3.141592653589793238462643383)


static struct Game
{
	bool left;
	bool right;
	bool forward;
	bool backward;
	float view[3];
} s;

static Game *GameStatics = &s;


static void Game_HandleInput()
{
	InputEvent event;

	while ( Input_PopEvent( &event ) )
	{
		printf( "Input Event: %d %d\n", event.type, event.key );

		if ( event.key == 80 )
			s.left = (event.type == EVENT_PRESS);
		if ( event.key == 79 )
			s.right = (event.type == EVENT_PRESS);
		if ( event.key == 82 )
			s.forward = (event.type == EVENT_PRESS);
		if ( event.key == 81 )
			s.backward = (event.type == EVENT_PRESS);
	}
}


void Game_Initialize()
{
	memset( &s, 0, sizeof( s ) );
}


void Game_Shutdown()
{
}


float *Game_GetView()
{
	return s.view;
}


void Game_Frame()
{
	Game_HandleInput();

	if ( s.left )
		s.view[2] += 0.1f;
	if ( s.right )
		s.view[2] -= 0.1f;

	if ( s.forward )
	{
		s.view[0] += -sin( s.view[2] * (float)PI / 180.0f );
		s.view[1] += cos( s.view[2] * (float)PI / 180.0f );
	}

	if ( s.backward )
	{
		s.view[0] -= -sin( s.view[2] * (float)PI / 180.0f );
		s.view[1] -= cos( s.view[2] * (float)PI / 180.0f );
	}

	while ( s.view[2] >= 360.0f )
		s.view[2] -= 360.0f;

	while ( s.view[2] < 0.0f )
		s.view[2] += 360.0f;

	printf( "view: %f %f %f\n", s.view[0], s.view[1], s.view[2] );
}
