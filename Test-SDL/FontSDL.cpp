#include "Main.h"

FontSDL::FontSDL()
	: _font(0)
{

}

FontSDL::~FontSDL()
{
	Release();
}

bool FontSDL::Load(cchar* file, uchar size)
{
    _font = TTF_OpenFont(file, size);
    if (_font == 0)
	{
       Message(SDL_MESSAGEBOX_ERROR, TTF_GetError());
		return false;
	}

	return Font::Load(file, size);
}

void FontSDL::Release()
{
	TTF_CloseFont(_font);
}

usint FontSDL::GetTextWidth(cchar* text) const
{
	int width;
	TTF_SizeUTF8(_font, text, &width, 0);
	return width;
}

usint FontSDL::GetTextHeight(cchar* text) const
{
	int height;
	TTF_SizeUTF8(_font, text, 0, &height);
	return height;
}