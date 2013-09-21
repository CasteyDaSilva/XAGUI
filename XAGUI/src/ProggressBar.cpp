#include "XAGUI.h"

namespace XAGUI
{

ProggressBar::ProggressBar()
	: _proggressWidth(0)
{

}

ProggressBar::ProggressBar(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _proggressWidth(0)
{
	ParseProperties(element);
}

ProggressBar::~ProggressBar()
{
	
}

void ProggressBar::ParseProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("proggress");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == '%')
			SetProggress(xaih::StrToUInt(xaih::ParseString(string, "%").c_str()));
	}
	else
	{
		SetProggress(0);
	}
}

void ProggressBar::SetProggress(uchar proggress)
{
	_proggress = proggress;
	SetProggressWidth(static_cast<usint>(GetSrcWidth(GetState()) * (proggress / 100.0f)));
}

void ProggressBar::SetProggressWidth(usint proggressWidth)
{
	_proggressWidth = proggressWidth;
}

void ProggressBar::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetProggressWidth(), 
			GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), GetProggressWidth(), 
			GetSrcHeight(GetState()), GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()), 
			GetAlpha(GetState()));

		Control::Render();
	}
}

};