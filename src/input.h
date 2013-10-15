#ifndef __INPUT_H__
#define __INPUT_H__

enum EventType
{
	EVENT_PRESS,
	EVENT_RELEASE
};


struct InputEvent
{
	EventType type;
	int key;
};


void Input_Initialize();
void Input_Shutdown();
void Input_Frame();

void Input_PushEvent( const InputEvent *event );
bool Input_PopEvent( InputEvent *event );

#endif // #ifndef __INPUT_H__
