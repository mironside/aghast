#ifndef __RENDER_H__
#define __RENDER_H__

void Render_Initialize();
void Render_Shutdown();
void Render_DrawFOV( float view[3] );
void Render_BeginFrame();
void Render_EndFrame();

#endif // #ifndef __RENDER_H__
