#include "modex.h"
#include <assert.h>
#include <memory.h>
#include <SDL.h>

static unsigned char *g_modeXFramebuffer;
static SDL_Texture *g_modeXFramebufferTexture;


void ModeX_Init( SDL_Renderer *renderer )
{
	g_modeXFramebuffer = (unsigned char *)malloc( sizeof( unsigned int ) * MODEX_SCREEN_WIDTH * MODEX_SCREEN_HEIGHT );
	g_modeXFramebufferTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, MODEX_SCREEN_WIDTH, MODEX_SCREEN_HEIGHT );
}


void ModeX_Shutdown()
{
	SDL_DestroyTexture( g_modeXFramebufferTexture );
	free( g_modeXFramebuffer );
}


void ModeX_SetPixel( unsigned int x, unsigned int y, unsigned int color )
{
	assert( x < MODEX_SCREEN_WIDTH );
	assert( y < MODEX_SCREEN_HEIGHT );

	((unsigned int *)g_modeXFramebuffer)[y * MODEX_SCREEN_WIDTH + x] = color;
}


void *ModeX_GetFramebuffer()
{
	assert( g_modeXFramebuffer );
	return g_modeXFramebuffer;
}


void ModeX_Present( SDL_Renderer *renderer )
{
	void *pixels;
	int pitch;

	SDL_LockTexture( g_modeXFramebufferTexture, NULL, &pixels, &pitch );
	memcpy( pixels, g_modeXFramebuffer, sizeof( unsigned int ) * MODEX_SCREEN_WIDTH * MODEX_SCREEN_HEIGHT );
	SDL_UnlockTexture( g_modeXFramebufferTexture );
	SDL_RenderCopy( renderer, g_modeXFramebufferTexture, NULL, NULL );
}

