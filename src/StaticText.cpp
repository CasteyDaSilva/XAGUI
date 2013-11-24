#include "XAGUI.h"

namespace XAGUI
{

StaticText::StaticText()
	: _font(0), _texture(0), _red(255), _green(255), _blue(255), _alpha(255)
{

}

StaticText::~StaticText()
{
	Release();
}

void StaticText::Release()
{
	SDL_DestroyTexture(_texture);
}

void StaticText::SetFont(cchar* file, sint size)
{
	if (size > 0)
	{
		_font = static_cast<Font*>(XAGUI::GetRenderer()->GetFont(file, static_cast<uchar>(size)));
	}
	else
	{
		_font = static_cast<Font*>(XAGUI::GetRenderer()->GetFont(file, GetFont()->GetSize()));
	}
	Set(Get());
}

void StaticText::Set(cchar* text)
{
	_text = text;

	Release();

	SDL_Color color;
	color.r = GetRed(); 
	color.g = GetGreen(); 	
	color.b = GetBlue(); 
	color.a = GetAlpha();

	SDL_Surface* surface = TTF_RenderUTF8_Solid(GetFont()->Get(), Get(), color);
	_texture = SDL_CreateTextureFromSurface(XAGUI::GetRenderer()->Get(), surface);
	SDL_SetTextureAlphaMod(_texture, color.a);
	SDL_FreeSurface(surface);
}

void StaticText::SetColor(uchar red, uchar green, uchar blue, uchar alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;

	Set(Get());
}

};