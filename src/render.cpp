#include "render.h"
#include <math.h>
#include "modex.h"
#include <memory.h>
#include <SDL.h>


const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 960;
#define PI (3.141592653589793238462643383)


static struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} s;


static void Render_DrawColumn( unsigned int column, unsigned int height, unsigned int color )
{
	unsigned int y;
	for ( y = 0; y < height; y++ )
	{
		ModeX_SetPixel( column, ((MODEX_SCREEN_HEIGHT - height) / 2) + y, color );
	}
}


void Render_DrawFOV( float view[3] )
{
	unsigned int column;
	float px;
	float py;
	float pd;

	px = sinf( view[2] * (float)PI / 180.0f );
	py = cosf( view[2] * (float)PI / 180.0f );
	pd = 100.0f + (px * view[0] + py * view[1]);

	for ( column = 0; column < MODEX_SCREEN_WIDTH; column++ )
	{
		float vx;
		float vy;
		float vd;
		float h;
		float theta;
		unsigned int color;
		
		theta = ((float)column - (float)MODEX_SCREEN_WIDTH / 2.0f) * (60.0f / (float)MODEX_SCREEN_WIDTH) * ((float)PI / 180.0f);
		vx = sin( theta );
		vy = cos( theta );
		vd = pd * (px * vx + py * vy);
		h = vd / cos( theta );
		color = (unsigned int)(255.0f / (100.0f / vd));

		Render_DrawColumn( column, (int)h, color );
	}
}


void Render_Initialize()
{
	s.window = SDL_CreateWindow( "Example", 32, 32, WINDOW_WIDTH, WINDOW_HEIGHT, 0 );
	s.renderer = SDL_CreateRenderer( s.window, -1, SDL_RENDERER_ACCELERATED /*SDL_RENDERER_SOFTWARE*/ );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	ModeX_Init( s.renderer );
}


void Render_Shutdown()
{
	ModeX_Shutdown();

	SDL_DestroyRenderer( s.renderer );
	SDL_DestroyWindow( s.window );
}


void Render_BeginFrame()
{
	memset( ModeX_GetFramebuffer(), 0x80, sizeof( unsigned int ) * MODEX_SCREEN_WIDTH * MODEX_SCREEN_HEIGHT );
}


void Render_EndFrame()
{
	ModeX_Present( s.renderer );
	SDL_RenderPresent( s.renderer );
}
