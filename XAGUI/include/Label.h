#ifndef XAGUI_LABEL_H
#define XAGUI_LABEL_H

class Label : public Control
{
	public:

		Label();

		Label(tinyxml2::XMLElement* element, Control* parent);

		virtual ~Label();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void Render();

		virtual inline cchar* GetRootText() const { return _text->Get(); }

		virtual inline Text* GetText() const { return _text; }

		virtual void SetText(cchar* text);

		virtual void SetText(cchar* file, uchar size, cchar* text);
		
		virtual void SetWidth(usint width);

		virtual void SetHeight(usint height);

		virtual void SetColor(uchar red, uchar green, uchar blue, uchar alpha);

		virtual void SetColorHover(uchar redHover, uchar greenHover, uchar blueHover, uchar alphaHover);

		virtual void SetColorPressed(uchar redPressed, uchar greenPressed, uchar bluePressed, 
			uchar alphaPressed);

		virtual void SetColorDisabled(uchar redDisabled, uchar greenDisabled, uchar blueDisabled, 
			uchar alphaDisabled);

	protected:

		Text* _text;
};

#endif
