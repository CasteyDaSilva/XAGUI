#include "XAGUI.h"

namespace XAGUI
{

Renderer* XAGUI::_renderer = 0;
Texture* XAGUI::_skin = 0;
TextInput XAGUI::_startTextInput = 0;
TextInput XAGUI::_stopTextInput = 0;
bool XAGUI::_textInputStarted = false;

void XAGUI::StartTextInput()
{
	if (!_textInputStarted && _startTextInput != 0)
	{
		_startTextInput();
		_textInputStarted = true;
	}
}

void XAGUI::StopTextInput()
{
	if (_textInputStarted && _stopTextInput != 0)
	{
		_stopTextInput();
		_textInputStarted = false;
	}
}

void XAGUI::SetRenderer(Renderer* renderer)
{
	_renderer = renderer;
}

void XAGUI::SetSkin(Texture* skin)
{
	_skin = skin;
}

void XAGUI::SetStartTextInput(TextInput startTextInput)
{
	_startTextInput = startTextInput;
}

void XAGUI::SetStopTextInput(TextInput stopTextInput)
{
	_stopTextInput = stopTextInput;
}

};