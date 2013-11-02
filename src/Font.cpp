#include "XAGUI.h"

namespace XAGUI
{

Font::Font()
	: _size(0)
{

}

Font::~Font()
{

}

bool Font::Load(cchar* file, uchar size)
{
	_file = file;
	_size = size;
	return true;
}

};
