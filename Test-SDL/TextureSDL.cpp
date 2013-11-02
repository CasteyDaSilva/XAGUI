#include "Main.h"

TextureSDL::TextureSDL()
	: _texture(0)
{

}

TextureSDL::~TextureSDL()
{
	Release();
}

bool TextureSDL::Load(cchar* file)
{
	SDL_Surface* surface = IMG_Load(file);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
	_texture = SDL_CreateTextureFromSurface(renderer->Get(), surface);
    if (_texture == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, IMG_GetError());
        return false;
    }

	return true;
}

void TextureSDL::Release()
{
	SDL_DestroyTexture(_texture);
}
