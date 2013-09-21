#include "XAGUI.h"

namespace XAGUI
{

Label::Label()
	: _text(0)
{

}

Label::Label(tinyxml2::XMLElement* element, Control* parent)
	: _text(0)
{
	SetParent(parent);
	ParseProperties(element);
}

Label::~Label()
{
	SAFE_DELETE(_text);	
}

void Label::ParseProperties(tinyxml2::XMLElement* element)
{
	uchar fontSize;
	std::string string = element->Attribute("fontSize");
	if (*string.rbegin() == '%')
	{
		fontSize = static_cast<uchar>(XAGUI::GetRenderer()->GetBackBufferHeight() / 8 * 
			xaih::StrToUInt(xaih::ParseString(string, "%").c_str()));
	}
	else
	{
		xaih::StrToUChar(string.c_str(), &fontSize);
	}

	cchar* cstring = element->Attribute("text"); 
	if (cstring == 0)
		cstring = "";
	
	SetText(element->Attribute("font"), element->UnsignedAttribute("fontSize"), cstring);

	Control::ParseProperties(element);
}

void Label::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(_text, GetAbsX(), GetAbsY());
		Control::Render();
	}
}

void Label::SetText(cchar* text)
{
	_text->Set(text);
	SetWidth(0);
	SetHeight(0);
}

void Label::SetText(cchar* file, uchar size, cchar* text)
{
	_text = XAGUI::GetRenderer()->GetText(file, size, text);
	SetWidth(0);
	SetHeight(0);
}

void Label::SetWidth(usint width)
{
	Control::SetWidth(_text->GetFont()->GetTextWidth(_text->Get()));
}

void Label::SetHeight(usint height)
{
	Control::SetHeight(_text->GetFont()->GetTextHeight(_text->Get()));
}

void Label::SetColor(uchar red, uchar green, uchar blue, uchar alpha)
{
	Control::SetColor(red, green, blue, alpha);
	_text->SetColor(red, green, blue, alpha);
}

void Label::SetColorHover(uchar redHover, uchar greenHover, uchar blueHover, uchar alphaHover)
{
	Control::SetColorHover(redHover, greenHover, blueHover, alphaHover);
	_text->SetColor(redHover, greenHover, blueHover, alphaHover);
}

void Label::SetColorPressed(uchar redPressed, uchar greenPressed, uchar bluePressed, uchar alphaPressed)
{
	Control::SetColorPressed(redPressed, greenPressed, bluePressed, alphaPressed);
	_text->SetColor(redPressed, greenPressed, bluePressed, alphaPressed);
}

void Label::SetColorDisabled(uchar redDisabled, uchar greeDisabled, uchar blueDisabled, 
							   uchar alphaDisabled)
{
	Control::SetColorDisabled(redDisabled, greeDisabled, blueDisabled, alphaDisabled);
	_text->SetColor(redDisabled, greeDisabled, blueDisabled, alphaDisabled);
}

};