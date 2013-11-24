#include "XAGUI.h"

namespace XAGUI
{

Renderer* XAGUI::_renderer = 0;
Texture* XAGUI::_skin = 0;
bool XAGUI::_textInputStarted = false;

void XAGUI::StartTextInput()
{
	// We don't want to restart text input.
	if (!_textInputStarted)
	{
		SDL_StartTextInput();
		_textInputStarted = true;
	}
}

void XAGUI::StopTextInput()
{
	// We don't want to restop text input.
	if (_textInputStarted)
	{
		SDL_StopTextInput();
		_textInputStarted = false;
	}
}

void XAGUI::SetRenderer(Renderer* renderer) { _renderer = renderer; }

void XAGUI::SetSkin(Texture* skin) { _skin = skin; }

};