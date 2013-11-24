#include "XAGUI.h"

namespace XAGUI
{

ProggressBar::ProggressBar()
	: _proggress(0), _proggressWidth(0)
{

}

ProggressBar::ProggressBar(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _proggress(0), _proggressWidth(0)
{
	ReadProperties(element);
}

ProggressBar::~ProggressBar()
{
	
}

void ProggressBar::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("proggress");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == '%')
			SetProggress(static_cast<uchar>(xaih::StrToUInt(xaih::ParseString(string, "%").c_str())));
	}
}

void ProggressBar::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetSrcWidth() * 
			(GetProggress() / 100), GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), 
			GetSrcWidth() * (GetProggress() / 100), GetSrcHeight(), GetColor(GetState()));
		Control::Render();
	}
}

};