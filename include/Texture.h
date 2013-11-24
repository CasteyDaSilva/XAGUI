#ifndef XAGUI_TEXTURE_H
#define XAGUI_TEXTURE_H

class Texture
{
	public:

		/**
		 * Constructor
		 */
		Texture();

		/**
		 * Destructor
		 */
		virtual ~Texture();

		/**
		 * Loads texture from file.
		 * @param file Path to texture file.
		 */
		virtual bool Load(cchar* file);

		/**
		 * Loads texture from file.
		 * @param file Path to texture file.
		 * @param keyColor
		 */
		virtual bool Load(cchar* file, SDL_Color keyColor);

		void Release();
		 
		inline SDL_Texture* Get() const { return _texture; }

	private:

		SDL_Texture* _texture;
};

#endif
