#ifndef XAGUI_TEST_MAIN_H
#define XAGUI_TEST_MAIN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <XAGUI.h>

#include "RendererSDL.h"

#define SCREEN_WIDTH renderer->GetBackBufferWidth()
#define SCREEN_HEIGHT renderer->GetBackBufferHeight()

void Message(uint flags, cchar* message);

extern RendererSDL* renderer;

extern char buffer[MAX_BUFFER];

#endif