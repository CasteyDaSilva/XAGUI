#ifndef XAGUI_RENDERER_H
#define XAGUI_RENDERER_H

class Renderer
{
	public:

		/**
		 * Constructor
		 * @param window
		 * @param backBufferWidth Back buffer width.
		 * @param backBufferHeight Back buffer height.
		 */
		Renderer(SDL_Window* window, usint backBufferWidth, usint backBufferHeight);

		/**
		 * Destructor
		 */
		virtual ~Renderer();

		bool Initialize();

		void Clear();

		/**
		 * Renders static text.
		 * @param staticText Pointer to static text.
		 * @param x X position
		 * @param y Y position
		 */
		virtual void Render(StaticText* staticText, sint x, sint y);

		/**
		 * Renders text.
		 * @param font Pointer to font object.
		 * @param text Text
		 * @param x X position
		 * @param y Y position
		 * @param color .
		 */
		virtual void Render(Font* font, cchar* text, sint x, sint y, SDL_Color color);

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
		 * @param color .
		 */
		virtual void Render(Texture* texture, sint x, sint y, usint width, usint height, usint srcX, 
			usint srcY, usint srcWidth, usint srcHeight, SDL_Color color);
		
		void Present();

		void Release();

		inline SDL_Renderer* Get() const { return _renderer; }

		/**
		 * Returns pointer to texture object.
		 * @param file Path to texture file.
		 * @return Pointer to texture object.
		 */
		virtual Texture* GetTexture(cchar* file) const;

		/**
		 * Returns pointer to font object.
		 * @param file Path to font file.
		 * @param size Size of font.
		 * @return Pointer to font object.
		 */
		virtual Font* GetFont(cchar* file, usint size) const; 
		
		/**
		 * Returns pointer to static text object.
		 * @param file Path to font file.
		 * @param size Size of font.
		 * @param text Text
		 * @return Pointer to static text object.
		 */
		virtual StaticText* GetStaticText(cchar* file, usint size, cchar* text) const; 

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

	protected:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		usint _backBufferWidth;
		usint _backBufferHeight;

		SDL_Surface* _surface;
		SDL_Texture* _texture;
		SDL_Rect _src;
		SDL_Rect _dst;

		static std::vector<Font*> _fonts;
};

#endif
