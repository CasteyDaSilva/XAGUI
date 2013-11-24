#include "XAGUI.h"

namespace XAGUI
{

Texture::Texture()
	: _texture(0)
{

}

Texture::~Texture()
{
	Release();
}

bool Texture::Load(cchar* file)
{
	SDL_Surface* surface = IMG_Load(file);
	_texture = SDL_CreateTextureFromSurface(XAGUI::GetRenderer()->Get(), surface);
    if (_texture == 0) return false;
	return true;
}

bool Texture::Load(cchar* file, SDL_Color keyColor)
{
	SDL_Surface* surface = IMG_Load(file);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, keyColor.r, keyColor.g, keyColor.b));
	_texture = SDL_CreateTextureFromSurface(XAGUI::GetRenderer()->Get(), surface);
    if (_texture == 0) return false;
	return true;
}

void Texture::Release()
{
	SDL_DestroyTexture(_texture);
}


};
