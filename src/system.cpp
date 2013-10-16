#include "system.h"
#include "input.h"
#include <SDL.h>
#include <memory.h>


bool System_HandleEvents()
{
	SDL_Event e;

	while ( SDL_PollEvent( &e ) )
	{
		if ( e.type == SDL_QUIT )
			return false;

		if ( e.type == SDL_KEYDOWN )
		{
			InputEvent event;

			memset( &event, 0, sizeof( InputEvent ) );
			event.type = EVENT_PRESS;
			event.key = e.key.keysym.scancode;
			Input_PushEvent( &event );
		}	
		else if ( e.type == SDL_KEYUP )
		{
			InputEvent event;

			memset( &event, 0, sizeof( InputEvent ) );
			event.type = EVENT_RELEASE;
			event.key = e.key.keysym.scancode;
			Input_PushEvent( &event );
		}
	}

	return true;
}

