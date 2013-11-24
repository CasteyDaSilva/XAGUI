#include "XAGUI.h"

namespace XAGUI
{

Font::Font()
	: _font(0), _size(0)
{

}

Font::~Font()
{
	Release();
}

bool Font::Load(cchar* file, usint size)
{
	_font = TTF_OpenFont(file, size);
    if (_font == 0) return false;
	_file = file;
	_size = size;
	return true;
}

void Font::Release()
{
	TTF_CloseFont(_font);
}

int Font::GetTextWidth(cchar* text) const
{
	int width;
	TTF_SizeUTF8(_font, text, &width, 0);
	return width;
}

int Font::GetTextHeight(cchar* text) const
{
	int height;
	TTF_SizeUTF8(_font, text, 0, &height);
	return height;
}

};
