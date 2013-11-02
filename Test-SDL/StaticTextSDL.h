#ifndef XAGUI_TEST_STATIC_TEXT_SDL_H
#define XAGUI_TEST_STATIC_TEXT_SDL_H

class StaticTextSDL : public XAGUI::StaticText
{
	public:

		StaticTextSDL();

		virtual ~StaticTextSDL();

		void Release();

		inline FontSDL* GetFont() const { return _font; }

		inline SDL_Texture* GetTexture() const { return _texture; }

		void SetFont(cchar* file, sint size = -1);

		void Set(cchar* text);

		void SetColor(uchar red, uchar green, uchar blue, uchar alpha);

	private:

		FontSDL* _font;
		SDL_Texture* _texture;
};

#endif