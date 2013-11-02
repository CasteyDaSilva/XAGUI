#ifndef XAGUI_TEST_TEXTURE_SDL_H
#define XAGUI_TEST_TEXTURE_SDL_H

class TextureSDL : public XAGUI::Texture
{
	public:

		TextureSDL();

		virtual ~TextureSDL();

		bool Load(cchar* file);

		void Release();

		inline SDL_Texture* Get() const { return _texture; }

	private:

		SDL_Texture* _texture;
};

#endif