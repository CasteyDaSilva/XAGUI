#include "XAGUI.h"

namespace XAGUI
{

Label::Label()
	: _staticText(0)
{

}

Label::Label(tinyxml2::XMLElement* element, Control* parent)
	: _staticText(0)
{
	SetParent(parent);
	ReadProperties(element);
}

Label::~Label()
{
	SAFE_DELETE(_staticText);	
}

void Label::ReadProperties(tinyxml2::XMLElement* element)
{
	usint fontSize = 0;
	std::string string = element->Attribute("fSize");
	if (*string.rbegin() == '%')
	{
		fontSize = static_cast<usint>(XAGUI::GetRenderer()->GetBackBufferHeight() / 7.0f * 
			(xaih::StrToUInt(xaih::ParseString(string, "%").c_str()) / 100.0f));
	}
	else
	{
		fontSize = xaih::StrToUInt(string.c_str());
	}

	cchar* cstring = element->Attribute("text"); 
	if (cstring == 0)
		cstring = "";

	SetText(element->Attribute("font"), fontSize, cstring);

	Control::ReadProperties(element);
}

void Label::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(_staticText, GetAbsX(), GetAbsY());
		Control::Render();
	}
}

void Label::SetText(cchar* text)
{
	_staticText->Set(text);
	SetWidth(0);
	SetHeight(0);
}

void Label::SetText(cchar* file, usint size, cchar* text)
{
	_staticText = XAGUI::GetRenderer()->GetStaticText(file, size, text);
	SetWidth(0);
	SetHeight(0);
}

void Label::SetWidth(usint width)
{
	Control::SetWidth(_staticText->GetFont()->GetTextWidth(_staticText->Get()));
}

void Label::SetHeight(usint height)
{
	Control::SetHeight(_staticText->GetFont()->GetTextHeight(_staticText->Get()));
}

void Label::SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha)
{
	Control::SetColor(controlState, red, green, blue, alpha);
	_staticText->SetColor(red, green, blue, alpha);
}

void Label::SetColor(ControlState controlState, SDL_Color color)
{
	Control::SetColor(controlState, color);
	_staticText->SetColor(color.r, color.g, color.b, color.a);
}

};