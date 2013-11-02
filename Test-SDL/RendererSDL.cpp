#include "Main.h"

std::vector<FontSDL*> RendererSDL::_fonts;

RendererSDL::RendererSDL(SDL_Window* window, usint backBufferWidth, usint backBufferHeight)
	: Renderer(backBufferWidth, backBufferHeight), _window(window), _renderer(0), _surface(0), 
	_texture(0)
{

}

RendererSDL::~RendererSDL()
{
	for (uint i = 0; i < _fonts.size(); i++)
		delete _fonts[i];
}

bool RendererSDL::Initialize()
{
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, SDL_GetError());
        return false;
    }
	
	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		Message(SDL_MESSAGEBOX_ERROR, TTF_GetError());
		return false;
	}

	return true;
}

void RendererSDL::Clear()
{
	SDL_RenderClear(_renderer);
}

void RendererSDL::Render(XAGUI::StaticText* staticText, sint x, sint y)
{
	Render(static_cast<StaticTextSDL*>(staticText), x, y);
}

void RendererSDL::Render(StaticTextSDL* staticText, sint x, sint y)
{
	_dst.x = x;
	_dst.y = y;

	_texture = staticText->GetTexture();
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_RenderCopy(_renderer, _texture, 0, &_dst);
}

void RendererSDL::Render(XAGUI::Font* font, cchar* text, sint x, sint y, uchar red, uchar green, 
						 uchar blue, uchar alpha)
{
	_dst.x = x;
	_dst.y = y;
	
	_color.r = red;
	_color.g = green;
	_color.b = blue;

	_surface = TTF_RenderUTF8_Solid(static_cast<FontSDL*>(font)->Get(), text, _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_SetTextureAlphaMod(_texture, alpha);
	SDL_RenderCopy(_renderer, _texture, 0, &_dst);
	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);
}

void RendererSDL::Render(XAGUI::Texture* texture, sint x, sint y, usint width, usint height, usint srcX, 
						 usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue,
						 uchar alpha)
{
	Render(static_cast<TextureSDL*>(texture), x, y, width, height, srcX, srcY, srcWidth,
		srcHeight, red, green, blue, alpha);
}

void RendererSDL::Render(TextureSDL* texture, sint x, sint y, usint width, usint height, usint srcX, 
						 usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue)
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
	SDL_SetTextureColorMod(_texture, red, green, blue);
	SDL_RenderCopy(_renderer, _texture, &_src, &_dst);
}

void RendererSDL::Render(TextureSDL* texture, sint x, sint y, usint width, usint height, usint srcX, 
						 usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue, 
						 uchar alpha)
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
	SDL_SetTextureColorMod(_texture, red, green, blue);
	SDL_SetTextureAlphaMod(_texture, alpha);
	SDL_RenderCopy(_renderer, _texture, &_src, &_dst);
}

void RendererSDL::Present()
{
	SDL_RenderPresent(_renderer);
}

void RendererSDL::Release()
{
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(_renderer);
}

TextureSDL* RendererSDL::GetTexture(cchar* file) const
{
	TextureSDL* texture = new TextureSDL();
	if (!texture->Load(file))
	{
		delete texture;
		return 0;
	}
	return texture;
}

FontSDL* RendererSDL::GetFont(cchar* file, uchar size) const
{
	// Check if font already exists...
	for (uint i = 0; i < _fonts.size(); i++)
	{
		if (strcmp(file, _fonts[i]->GetFile()) == 0 && _fonts[i]->GetSize() == size)
			// ...if yes we need to return font.
			return _fonts[i];
	}

	// ...if not, we need to create new one...
	FontSDL* font = new FontSDL();
	font->Load(file, size);

	// ..and add to the font list.
	_fonts.push_back(font);

	return font;
}

StaticTextSDL* RendererSDL::GetStaticText(cchar* file, uchar size, cchar* text) const
{
	StaticTextSDL* staticText = new StaticTextSDL();
	staticText->SetFont(file, size); 
	staticText->Set(text);
	return staticText;
}