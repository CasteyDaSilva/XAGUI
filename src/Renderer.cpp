#include "XAGUI.h"

namespace XAGUI
{

std::vector<Font*> Renderer::_fonts;

Renderer::Renderer(SDL_Window* window, usint backBufferWidth, usint backBufferHeight)
	: _window(window), _renderer(0), _backBufferWidth(backBufferWidth), 
	_backBufferHeight(backBufferHeight), _surface(0), _texture(0)
{

}

Renderer::~Renderer()
{
	for (uint i = 0; i < _fonts.size(); i++) delete _fonts[i];
}

bool Renderer::Initialize()
{
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (_renderer == 0) return false;
	
	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) == 0) return false;
	if (TTF_Init() == -1) return false;

	return true;
}

void Renderer::Clear()
{
	SDL_RenderClear(_renderer);
}

void Renderer::Render(StaticText* staticText, sint x, sint y)
{
	_dst.x = x;
	_dst.y = y;

	_texture = staticText->GetTexture();
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_RenderCopy(_renderer, _texture, 0, &_dst);
}

void Renderer::Render(Font* font, cchar* text, sint x, sint y, SDL_Color color)
{
	_dst.x = x;
	_dst.y = y;

	_surface = TTF_RenderUTF8_Solid(font->Get(), text, color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_SetTextureAlphaMod(_texture, color.a);
	SDL_RenderCopy(_renderer, _texture, 0, &_dst);
	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);
}

void Renderer::Render(Texture* texture, sint x, sint y, usint width, usint height, usint srcX, 
					  usint srcY, usint srcWidth, usint srcHeight, SDL_Color color)
{
	_dst.x = x;
	_dst.y = y;
	_dst.w = width;
	_dst.h = height;

	_src.x = srcX;
	_src.y = srcY;
	_src.w = srcWidth;
	_src.h = srcHeight;

	_texture = texture->Get();
	SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(_texture, color.a);
	SDL_RenderCopy(_renderer, _texture, &_src, &_dst);
}

void Renderer::Present()
{
	SDL_RenderPresent(_renderer);
}

void Renderer::Release()
{
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(_renderer);
}

Texture* Renderer::GetTexture(cchar* file) const
{
	Texture* texture = new Texture();
	if (!texture->Load(file))
	{
		delete texture;
		return 0;
	}
	return texture;
}

Font* Renderer::GetFont(cchar* file, usint size) const
{
	// Check if font already exists...
	for (uint i = 0; i < _fonts.size(); i++)
	{
		if (strcmp(file, _fonts[i]->GetFile()) == 0 && _fonts[i]->GetSize() == size) return _fonts[i];
	}

	// ...if not, we need to create new one...
	Font* font = new Font();
	font->Load(file, size);

	// ..and add to the font list.
	_fonts.push_back(font);
	return font;
}

StaticText* Renderer::GetStaticText(cchar* file, usint size, cchar* text) const
{
	StaticText* staticText = new StaticText();
	staticText->SetFont(file, size); 
	staticText->Set(text);
	return staticText;
}

};
