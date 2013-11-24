#ifndef XAGUI_FONT_H
#define XAGUI_FONT_H

class Font
{
	public:

		/**
		 * Constructor
		 */
		Font();

		/**
		 * Destructor
		 */
		virtual ~Font();

		/**
		 * Loads fonts from file with specified size.
		 * @param file Path to font file.
		 * @param size Size of font.
		 */
		virtual bool Load(cchar* file, usint size);
		
		virtual void Release();

		inline TTF_Font* Get() const { return _font; }

		/**
		 * Returns path to font file.
		 * @return Path fo font file.
		 */
		virtual inline cchar* GetFile() const { return _file.c_str(); }

		/**
		 * Returns size of font.
		 * @return Size of font.
		 */
		virtual inline usint GetSize() const { return _size; }

		/**
		 * Measures text width.
		 * @param text Text to be measured.
		 * @return Text width.
		 */
		virtual int GetTextWidth(cchar* text) const;

		/**
		 * Measures text height.
		 * @param text Text to be measured.
		 * @return Text height.
		 */
		virtual int GetTextHeight(cchar* text) const;

	protected:

		TTF_Font* _font;
		std::string _file;
		usint _size;
};

#endif
