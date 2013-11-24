#ifndef XAGUI_STATIC_TEXT_H
#define XAGUI_STATIC_TEXT_H

class StaticText
{
	public:

		/**
		 * Constructor
		 */
		StaticText();

		/**
		 * Destructor
		 */
		virtual ~StaticText();
		
		void Release();

		/**
		 * Returns pointer to font object.
		 * @return Pointer to font object.
		 */
		virtual inline Font* GetFont() const { return _font; }
		
		inline SDL_Texture* GetTexture() const { return _texture; }

		/**
		 * Returns text.
		 * @return Text
		 */
		virtual inline cchar* Get() const { return _text.c_str(); }

		/**
		 * Returns std::string.
		 * @return std::string
		 */
		virtual inline std::string GetString() { return _text; }
		
		/**
		 * Returns pointer to std::string object.
		 * @return Pointer to std::string object.
		 */
		virtual inline std::string* GetPointerToString() { return &_text; }

		/**
		 * Returns length of text.
		 * @return Length of text.
		 */
		virtual inline uint GetLength() const { return _text.length(); }
		
		/**
		 * Returns value of red channel.
		 * @return Value of red channel.
		 */
		virtual inline uchar GetRed() const { return _red; }

		/**
		 * Returns value of green channel.
		 * @return Value of green channel.
		 */
		virtual inline uchar GetGreen() const { return _green; }

		/**
		 * Returns value of blue channel.
		 * @return Value of blue channel.
		 */
		virtual inline uchar GetBlue() const { return _blue; }

		/**
		 * Returns value of alpha channel.
		 * @return Value of alpha channel.
		 */
		virtual inline uchar GetAlpha() const { return _alpha; }

		/**
		 * Sets font of static text.
		 * @param file Path to font file.
		 * @param size Size of font. -1 for unchanged font size.
		 */
		virtual void SetFont(cchar* file, sint size = -1);

		/**
		 * Sets text.
		 * @param text Text.
		 */
		virtual inline void Set(cchar* text);

		/**
		 * Sets color of static text.
		 * @param red Value for red channel of color.
		 * @param green Value for green channel of color.
		 * @param blue Value for blue channel of color.
		 * @param alpha Value for alpha channel of color.
		 */
		virtual void SetColor(uchar red, uchar green, uchar blue, uchar alpha);

	protected:

		Font* _font;
		SDL_Texture* _texture;
		std::string _text;
		uchar _red;
		uchar _green;
		uchar _blue; 
		uchar _alpha;
};

#endif
