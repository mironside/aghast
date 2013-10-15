#ifndef __MODEX_H__
#define __MODEX_H__

struct SDL_Renderer;

static const unsigned int MODEX_SCREEN_WIDTH = 320;
static const unsigned int MODEX_SCREEN_HEIGHT = 240;

void ModeX_Init( struct SDL_Renderer *renderer );
void ModeX_Shutdown();
void ModeX_Present( struct SDL_Renderer *renderer );

void *ModeX_GetFramebuffer();
void ModeX_SetPixel( unsigned int x, unsigned int y, unsigned int color );

#endif // #ifndef __MODEX_H__
