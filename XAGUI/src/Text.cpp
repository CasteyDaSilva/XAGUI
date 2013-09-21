#include "XAGUI.h"

namespace XAGUI
{

Text::Text()
	: _red(255), _green(255), _blue(255), _alpha(255)
{

}

Text::~Text()
{
	
}

void Text::Set(cchar* text)
{
	_text = text;
}

void Text::SetColor(uchar red, uchar green, uchar blue, uchar alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

};