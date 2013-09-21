#ifndef XAGUI_TEXT_H
#define XAGUI_TEXT_H

class Text
{
	public:

		Text();

		virtual ~Text();

		virtual Font* GetFont() const = 0;

		virtual inline cchar* Get() const { return _text.c_str(); }

		virtual inline std::string* GetPtrStdStr() { return &_text; }

		virtual inline uint GetLength() const { return _text.length(); }

		virtual inline uchar GetRed() const { return _red; }

		virtual inline uchar GetGreen() const { return _green; }

		virtual inline uchar GetBlue() const { return _blue; }

		virtual inline uchar GetAlpha() const { return _alpha; }

		virtual void SetFont(cchar* file, sint size = -1) = 0;

		virtual void Set(cchar* text);

		virtual void SetColor(uchar red, uchar green, uchar blue, uchar alpha);

		virtual operator const char* () const { return Get(); }

	protected:

		std::string _text;
		uchar _red;
		uchar _green;
		uchar _blue; 
		uchar _alpha;
};

#endif
