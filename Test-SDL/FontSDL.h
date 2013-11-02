#ifndef XAGUI_TEST_FONT_SDL_H
#define XAGUI_TEST_FONT_SDL_H

class FontSDL : public XAGUI::Font
{
	public:

		FontSDL();

		virtual ~FontSDL();

		virtual bool Load(cchar* file, uchar size);

		virtual void Release();

		inline TTF_Font* Get() const { return _font; }

		usint GetTextWidth(cchar* text) const;

		usint GetTextHeight(cchar* text) const;

	private:

		TTF_Font* _font;
};

#endif