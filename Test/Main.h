#ifndef XAGUI_TEST_MAIN_H
#define XAGUI_TEST_MAIN_H

#include <XAGUI.h>

#define SCREEN_WIDTH renderer->GetBackBufferWidth()
#define SCREEN_HEIGHT renderer->GetBackBufferHeight()

void Message(uint flags, cchar* message);

extern XAGUI::Renderer* renderer;

extern char buffer[MAX_BUFFER];

#endif