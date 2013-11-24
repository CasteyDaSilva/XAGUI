#include "XAGUI.h"

namespace XAGUI
{

CheckBox::CheckBox()
	: _checked(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_checkedSrcX[i] = 0;
		_checkedSrcY[i] = 0;
	}
}

CheckBox::CheckBox(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _checked(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_checkedSrcX[i] = 0;
		_checkedSrcY[i] = 0;
	}

	ReadProperties(element);
}

CheckBox::~CheckBox()
{

}

void CheckBox::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("cSrcX");
	if (cstring != 0)
		SetCheckedSrcX(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("cSrcY");
	if (cstring != 0)
		SetCheckedSrcY(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("chSrcX");
	if (cstring != 0) 
	{ 
		SetCheckedSrcX(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetCheckedSrcX(CONTROL_STATE_HOVER, GetCheckedSrcX(GetState()));
	}

	cstring = element->Attribute("chSrcY");
	if (cstring != 0) 
	{ 
		SetCheckedSrcY(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetCheckedSrcY(CONTROL_STATE_HOVER, GetCheckedSrcY(GetState()));
	}

	cstring = element->Attribute("caSrcX");
	if (cstring != 0) 
	{ 
		SetCheckedSrcX(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{
		SetCheckedSrcX(CONTROL_STATE_ACTIVE, GetCheckedSrcX(GetState()));
	}

	cstring = element->Attribute("caSrcY");
	if (cstring != 0)
	{ 
		SetCheckedSrcY(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{
		SetCheckedSrcY(CONTROL_STATE_ACTIVE, GetCheckedSrcY(GetState()));
	}

	cstring = element->Attribute("cdSrcX");
	if (cstring != 0) 
	{ 
		SetCheckedSrcX(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetCheckedSrcX(CONTROL_STATE_DISABLED, GetCheckedSrcX(GetState()));
	}

	cstring = element->Attribute("cdSrcY");
	if (cstring != 0)
	{ 
		SetCheckedSrcY(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring)); 
	}
	else
	{ 
		SetCheckedSrcY(CONTROL_STATE_DISABLED, GetCheckedSrcY(GetState()));
	}
}

void CheckBox::Render()
{
	if (IsVisible())
	{
		if (!_checked)
		{
			XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), 
				GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
				GetColor(GetState()));
		}
		else
		{
			XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), 
				GetHeight(), GetCheckedSrcX(GetState()), GetCheckedSrcY(GetState()), GetSrcWidth(), 
				GetSrcHeight(), GetColor(GetState()));
		}

		Control::Render();
	}
}

void CheckBox::SetCheckedSrcX(ControlState controlState, usint checkedsrcX)
{ 
	if (controlState == CONTROL_STATE_COUNT)
	{
		for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
			_checkedSrcX[i] = checkedsrcX;
	}
	else
	{
		_checkedSrcX[controlState] = checkedsrcX; 
	}
}

void CheckBox::SetCheckedSrcY(ControlState controlState, usint checkedsrcY)
{ 
	if (controlState == CONTROL_STATE_COUNT)
	{
		for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
			_checkedSrcY[i] = checkedsrcY;
	}
	else
	{
		_checkedSrcY[controlState] = checkedsrcY; 
	}
}

void CheckBox::OnClickEvent()
{
	(IsChecked()) ? SetChecked(false) : SetChecked(true); 
}

};