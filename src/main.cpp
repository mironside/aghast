#include <SDL.h>
#include <assert.h>
#include "modex.h"
#include <stdio.h>
#include <math.h>
#include <memory.h>

#define PI 3.141592653589793238462643383

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 960;

void Render_Frame();

int main( int argc, char **argv )
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init( SDL_INIT_VIDEO );

	window = SDL_CreateWindow( "Example", 32, 32, WINDOW_WIDTH, WINDOW_HEIGHT, 0 );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED /*SDL_RENDERER_SOFTWARE*/ );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	ModeX_Init( renderer );

	while ( 1 )
	{
		SDL_Event e;
		if ( SDL_PollEvent( &e ) )
		{
			if ( e.type == SDL_QUIT )
				break;
		}

		Render_Frame();
		ModeX_Present( renderer );
		SDL_RenderPresent( renderer );
	}

	ModeX_Shutdown();

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}

void Render_DrawColumn( unsigned int column, unsigned int height )
{
	unsigned int y;
	for ( y = 0; y < height; y++ )
	{
		ModeX_SetPixel( column, ((MODEX_SCREEN_HEIGHT - height) / 2) + y, 0xFFFFFFFF );
	}
}


void Render_DrawFOV()
{
	unsigned int column;

	float px;
	float py;
	float pd;

	static float t = -49.0f;
	static float dt = 0.1;

	//t += dt;
	if ( t > 49.0f || t < -49.0f)
	{
		dt = -dt;
	}

	px = sin( t * PI / 180.0f );
	py = cos( t * PI / 180.0f );
	pd = 100.0f;

	for ( column = 0; column < MODEX_SCREEN_WIDTH; column++ )
	{
		float vx;
		float vy;
		float vd;
		float h;
		float theta;
		
		theta = ((int)column - (int)MODEX_SCREEN_WIDTH / 2) * (60.0f / (float)MODEX_SCREEN_WIDTH) * (PI / 180.0f);
		vx = sin( theta );
		vy = cos( theta );
		vd = pd * (px * vx + py * vy);
		h = vd / cos( theta );

		//printf( "%03d %f %f\n", column, vd, h );
		Render_DrawColumn( column, h );
	}
}


void Render_Frame()
{
	memset( ModeX_GetFramebuffer(), 0x80, sizeof( unsigned int ) * MODEX_SCREEN_WIDTH * MODEX_SCREEN_HEIGHT );
	Render_DrawFOV();
}
