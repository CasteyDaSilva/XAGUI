#ifndef XAGUI_TEST_RENDERER_SDL_H
#define XAGUI_TEST_RENDERER_SDL_H

#include "FontSDL.h"
#include "TextureSDL.h"
#include "StaticTextSDL.h"

class RendererSDL : public XAGUI::Renderer
{
	public:

		RendererSDL(SDL_Window* window, usint backBufferWidth, usint backBufferHeight);

		virtual ~RendererSDL();

		bool Initialize();

		void Clear();

		void Render(XAGUI::StaticText* staticText, sint x, sint y);

		void Render(StaticTextSDL* staticText, sint x, sint y);

		void Render(XAGUI::Font* font, cchar* text, sint x, sint y, uchar red = 255, uchar green = 255, 
			uchar blue = 255, uchar alpha = 255);

		void Render(XAGUI::Texture* texture, sint x, sint y, usint width, usint height, usint srcX, 
			usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue, uchar alpha);

		void Render(TextureSDL* texture, sint x, sint y, usint width, usint height, usint srcX, 
			usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue);

		void Render(TextureSDL* texture, sint x, sint y, usint width, usint height, usint srcX, 
			usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue, uchar alpha);

		void Present();

		void Release();

		inline SDL_Renderer* Get() const { return _renderer; }

		TextureSDL* GetTexture(cchar* file) const;

		FontSDL* GetFont(cchar* file, uchar size) const;

		StaticTextSDL* GetStaticText(cchar* file, uchar size, cchar* text) const;

	private:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		
		SDL_Surface* _surface;
		SDL_Texture* _texture;
		SDL_Rect _src;
		SDL_Rect _dst;
		SDL_Color _color;

		static std::vector<FontSDL*> _fonts;
};

#endif