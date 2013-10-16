#include <SDL.h>
#include "input.h"
#include "game.h"
#include "system.h"
#include "render.h"


const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 960;


int main( int argc, char **argv )
{
	SDL_Init( SDL_INIT_VIDEO );

	Render_Initialize();
	Input_Initialize();
	Game_Initialize();

	for ( ;; )
	{
		Input_Frame();
		if ( !System_HandleEvents() )
			break;
		Game_Frame();
		
		Render_BeginFrame();
		Render_DrawFOV( Game_GetView() );
		Render_EndFrame();
	}

	Game_Shutdown();
	Input_Shutdown();
	Render_Shutdown();

	SDL_Quit();

	return 0;
}
