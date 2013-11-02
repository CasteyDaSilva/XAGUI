#ifndef XAGUI_RENDERER_H
#define XAGUI_RENDERER_H

class Renderer
{
	public:

		/**
		 * Constructor
		 * @param backBufferWidth Back buffer width.
		 * @param backBufferHeight Back buffer height.
		 */
		Renderer(usint backBufferWidth, usint backBufferHeight);

		/**
		 * Destructor
		 */
		virtual ~Renderer();

		/**
		 * Renders static text.
		 * @param staticText Pointer to static text.
		 * @param x X position
		 * @param y Y position
		 */
		virtual void Render(StaticText* staticText, sint x, sint y) = 0;

		/**
		 * Renders text.
		 * @param font Pointer to font object.
		 * @param text Text
		 * @param x X position
		 * @param y Y position
		 * @param red Value for red channel of color.
		 * @param green Value for green channel of color.
		 * @param blue Value for blue channel of color.
		 * @param alpha Value for alpha channel of color.
		 */
		virtual void Render(Font* font, cchar* text, sint x, sint y, uchar red = 255, 
			uchar green = 255, uchar blue = 255, uchar alpha = 255) = 0;

		/**
		 * Renders texture.
		 * @param texture Pointer to texture object.
		 * @param x X position
		 * @param y Y position
		 * @param width Width
		 * @param height Height
		 * @param srcX X position of texture region.
		 * @param srcY Y position of texture region.
		 * @param srcWidth Width of texture region.
		 * @param srcHeight Height of texture region.
		 * @param red Value for red channel of color.
		 * @param green Value for green channel of color.
		 * @param blue Value for blue channel of color.
		 * @param alpha Value for alpha channel of color.
		 */
		virtual void Render(Texture* texture, sint x, sint y, usint width, usint height, usint srcX, 
			usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue, 
			uchar alpha) = 0;

		/**
		 * Returns pointer to texture object.
		 * You need to overload this function with your own return texture type.
		 * @param file Path to texture file.
		 * @return Pointer to texture object.
		 */
		virtual Texture* GetTexture(cchar* file) const = 0;

		/**
		 * Returns pointer to font object.
		 * You need to overload this function with your own return font type.
		 * @param file Path to font file.
		 * @param size Size of font.
		 * @return Pointer to font object.
		 */
		virtual Font* GetFont(cchar* file, uchar size) const = 0; 
		
		/**
		 * Returns pointer to static text object.
		 * @param file Path to font file.
		 * @param size Size of font.
		 * @param text Text
		 * @return Pointer to static text object.
		 */
		virtual StaticText* GetStaticText(cchar* file, uchar size, cchar* text) const = 0; 

		/**
		 * Returns back buffer width.
		 * @return Back buffer width.
		 */
		virtual inline usint GetBackBufferWidth() const { return _backBufferWidth; }

		/**
		 * Returns back buffer height.
		 * @return Back buffer height.
		 */
		virtual inline usint GetBackBufferHeight() const { return _backBufferHeight; }

		/**
		 * Sets back buffer width.
		 * @param backBufferWidth.
		 */
		virtual inline void SetBackBufferWidth(usint backBufferWidth) 
		{ _backBufferWidth = backBufferWidth; }

		/**
		 * Sets back buffer height.
		 * @param backBufferHeight.
		 */
		virtual inline void SetBackBufferHeight(usint backBufferHeight) 
		{ _backBufferHeight = backBufferHeight; }

	private:

		usint _backBufferWidth;
		usint _backBufferHeight;
};

#endif
