#ifndef XAGUI_TEXTURE_H
#define XAGUI_TEXTURE_H

class Texture
{
	public:

		Texture();

		virtual ~Texture();

		virtual bool Load(cchar* file) = 0;
};

#endif
