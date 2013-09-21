#ifndef XAGUI_FONT_H
#define XAGUI_FONT_H

class Font
{
	public:

		Font();

		virtual ~Font();

		virtual bool Load(cchar* file, uchar size);

		virtual inline cchar* GetFile() const { return _file.c_str(); }

		virtual inline uchar GetSize() const { return _size; }

		virtual usint GetTextWidth(cchar* text) const = 0;

		virtual usint GetTextHeight(cchar* text) const = 0;

	protected:

		std::string _file;
		uchar _size;
};

#endif
