#include "Main.h"

StaticTextSDL::StaticTextSDL()
	: _font(0), _texture(0)
{

}

StaticTextSDL::~StaticTextSDL()
{
	Release();
}

void StaticTextSDL::Release()
{
	SDL_DestroyTexture(_texture);
}

void StaticTextSDL::SetFont(cchar* file, sint size)
{
	if (size > 0)
	{
		_font = static_cast<FontSDL*>(XAGUI::XAGUI::GetRenderer()->GetFont(file, 
			static_cast<uchar>(size)));
	}
	else
	{
		_font = static_cast<FontSDL*>(XAGUI::XAGUI::GetRenderer()->GetFont(file, GetFont()->GetSize()));
	}
	Set(StaticText::Get());
}

void StaticTextSDL::Set(cchar* text)
{
	StaticText::Set(text);

	Release();

	SDL_Color color;
	color.r = StaticText::GetRed(); 
	color.g = StaticText::GetGreen(); 	
	color.b = StaticText::GetBlue(); 

	SDL_Surface* surface = TTF_RenderUTF8_Solid(GetFont()->Get(), StaticText::Get(), color);
	_texture = SDL_CreateTextureFromSurface(renderer->Get(), surface);
	SDL_SetTextureAlphaMod(_texture, StaticText::GetAlpha());
	SDL_FreeSurface(surface);
}

void StaticTextSDL::SetColor(uchar red, uchar green, uchar blue, uchar alpha)
{
	StaticText::SetColor(red, green, blue, alpha);
	Set(StaticText::Get());
}
