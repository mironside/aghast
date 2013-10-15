#include "input.h"
#include <memory.h>
#include <assert.h>


static const int INPUT_MAX_EVENT_COUNT = 128;


static struct
{
	InputEvent eventQueue[INPUT_MAX_EVENT_COUNT];
	int eventQueueCount;
	int eventQueueIndex;
} s;


void Input_Initialize()
{
	memset( &s, 0, sizeof( s ) );
}


void Input_Shutdown()
{
}


void Input_Frame()
{
	s.eventQueueCount = 0;
	s.eventQueueIndex = 0;
}


void Input_PushEvent( const InputEvent *event )
{
	assert( s.eventQueueCount + 1 < sizeof( s.eventQueue ) / sizeof( s.eventQueue[0] ) );
	memcpy( &s.eventQueue[s.eventQueueCount], event, sizeof( InputEvent ) );
	s.eventQueueCount++;
}


bool Input_PopEvent( InputEvent *event )
{
	if ( s.eventQueueIndex >= s.eventQueueCount )
		return false;

	memcpy( event, &s.eventQueue[s.eventQueueIndex], sizeof( InputEvent ) );
	s.eventQueueIndex++;

	return true;
}
