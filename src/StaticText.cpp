#include "XAGUI.h"

namespace XAGUI
{

StaticText::StaticText()
	: _red(255), _green(255), _blue(255), _alpha(255)
{

}

StaticText::~StaticText()
{
	
}

void StaticText::SetColor(uchar red, uchar green, uchar blue, uchar alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

};