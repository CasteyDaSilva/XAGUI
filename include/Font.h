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
		virtual bool Load(cchar* file, uchar size);

		/**
		 * Returns path to font file.
		 * @return Path fo font file.
		 */
		virtual inline cchar* GetFile() const { return _file.c_str(); }

		/**
		 * Returns size of font.
		 * @return Size of font.
		 */
		virtual inline uchar GetSize() const { return _size; }

		/**
		 * Measures text width.
		 * @param text Text to be measured.
		 * @return Text width.
		 */
		virtual usint GetTextWidth(cchar* text) const = 0;

		/**
		 * Measures text height.
		 * @param text Text to be measured.
		 * @return Text height.
		 */
		virtual usint GetTextHeight(cchar* text) const = 0;

	protected:

		std::string _file;
		uchar _size;
};

#endif
