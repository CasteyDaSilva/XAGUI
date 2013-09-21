#ifndef XAGUI_RENDERER_H
#define XAGUI_RENDERER_H

class Renderer
{
	public:

		Renderer(usint backBufferWdth, usint backBufferHeght);

		virtual ~Renderer();

		virtual void Render(Text* text, sint dstX, sint dstY) = 0;

		virtual void Render(Font* font, cchar* text, sint dstX, sint dstY, uchar red = 255, 
			uchar green = 255, uchar blue = 255, uchar alpha = 255) = 0;

		virtual void Render(Texture* texture, sint dstX, sint dstY, usint dstWidth, usint dstHeight,
			usint srcX, usint srcY, usint srcWidth, usint srcHeight, uchar red, uchar green, uchar blue, 
			uchar alpha) = 0;

		virtual Texture* GetTexture(cchar* file) const = 0;

		virtual Font* GetFont(cchar* file, uchar size) const = 0; 
		
		virtual Text* GetText(cchar* file, uchar size, cchar* text) const = 0; 

		virtual inline usint GetBackBufferWidth() const { return _backBufferWidth; }

		virtual inline usint GetBackBufferHeight() const { return _backBufferHeight; }

	private:

		usint _backBufferWidth;
		usint _backBufferHeight;
};

#endif
