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
		virtual bool Load(cchar* file) = 0;
};

#endif
