#include "XAGUI.h"

namespace XAGUI
{

CheckBox::CheckBox()
	: _checked(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcCheckedX[i] = 0;
		_srcCheckedY[i] = 0;
		_srcCheckedWidth[i] = 0;
		_srcCheckedHeight[i] = 0;
	}
}

CheckBox::CheckBox(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _checked(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcCheckedX[i] = 0;
		_srcCheckedY[i] = 0;
		_srcCheckedWidth[i] = 0;
		_srcCheckedHeight[i] = 0;
	}

	ParseProperties(element);
}

CheckBox::~CheckBox()
{

}

void CheckBox::ParseProperties(tinyxml2::XMLElement* element)
{
	Button::ParseProperties(element);

	cchar* cstring = element->Attribute("srcCheckedX");
	if (cstring != 0)
		SetSrcCheckedX(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcCheckedY");
	if (cstring != 0)
		SetSrcCheckedY(xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("srcCheckedWidth");
	if (cstring != 0)
		SetSrcCheckedWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcCheckedHeight");
	if (cstring != 0)
		SetSrcCheckedHeight(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcCheckedHoverX");
	if (cstring != 0) 
	{ 
		SetSrcCheckedHoverX(xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcCheckedHoverX(GetSrcCheckedX(GetState()));
	}

	cstring = element->Attribute("srcCheckedHoverY");
	if (cstring != 0) 
	{ 
		SetSrcCheckedHoverY(xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcCheckedHoverY(GetSrcCheckedY(GetState()));
	}

	cstring = element->Attribute("srcCheckedHoverWidth");
	if (cstring != 0) 
	{ 
		SetSrcCheckedHoverWidth(xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcCheckedHoverWidth(GetSrcCheckedWidth(GetState()));
	}

	cstring = element->Attribute("srcCheckedHoverHeight");
	if (cstring != 0)
	{ 
		SetSrcCheckedHoverHeight(xaih::StrToUInt(cstring)) ;
	}
	else
	{ 
		SetSrcCheckedHoverHeight(GetSrcCheckedHeight(GetState()));
	}

	cstring = element->Attribute("srcCheckedPressedX");
	if (cstring != 0) 
	{ 
		SetSrcCheckedPressedX(xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcCheckedPressedX(GetSrcCheckedX(GetState()));
	}

	cstring = element->Attribute("srcCheckedPressedY");
	if (cstring != 0)
	{ 
		SetSrcCheckedPressedY(xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcCheckedPressedY(GetSrcCheckedY(GetState()));
	}

	cstring = element->Attribute("srcCheckedPressedWidth");
	if (cstring != 0)
	{
		SetSrcCheckedPressedWidth(xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcCheckedPressedWidth(GetSrcCheckedWidth(GetState()));
	}

	cstring = element->Attribute("srcCheckedPressedHeight");
	if (cstring != 0) 
	{
		SetSrcCheckedPressedHeight(xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcCheckedPressedHeight(GetSrcCheckedHeight(GetState()));
	}

	cstring = element->Attribute("srcCheckedDisabledX");
	if (cstring != 0) 
	{ 
		SetSrcCheckedDisabledX(xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcCheckedDisabledX(GetSrcCheckedX(GetState()));
	}

	cstring = element->Attribute("srcCheckedDisabledY");
	if (cstring != 0)
	{ 
		SetSrcCheckedDisabledY(xaih::StrToUInt(cstring)); 
	}
	else
	{ 
		SetSrcCheckedDisabledY(GetSrcCheckedY(GetState()));
	}

	cstring = element->Attribute("srcCheckedDisabledWidth");
	if (cstring != 0) 
	{
		SetSrcCheckedDisabledWidth(xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcCheckedDisabledWidth(GetSrcCheckedWidth(GetState()));
	}

	cstring = element->Attribute("srcCheckedDisabledHeight");
	if (cstring != 0) 
	{
		SetSrcCheckedDisabledHeight(xaih::StrToUInt(cstring)); 
	}
	else 
	{
		SetSrcCheckedDisabledHeight(GetSrcCheckedHeight(GetState()));
	}
}

void CheckBox::OnClickEvent()
{
	_checked ? _checked = false : _checked = true; 
}

void CheckBox::SetSrcCheckedX(usint srcCheckedX)
{
	_srcCheckedX[CONTROL_STATE_NORMAL] = srcCheckedX;
}

void CheckBox::SetSrcCheckedY(usint srcCheckedY)
{
	_srcCheckedY[CONTROL_STATE_NORMAL] = srcCheckedY;
}

void CheckBox::SetSrcCheckedWidth(usint srcCheckedWidth)
{
	_srcCheckedWidth[CONTROL_STATE_NORMAL] = srcCheckedWidth;
}

void CheckBox::SetSrcCheckedHeight(usint srcCheckedHeight)
{
	_srcCheckedHeight[CONTROL_STATE_NORMAL] = srcCheckedHeight;
}

void CheckBox::SetSrcCheckedHoverX(usint srcCheckedHoverX)
{
	_srcCheckedX[CONTROL_STATE_HOVER] = srcCheckedHoverX;
}

void CheckBox::SetSrcCheckedHoverY(usint srcCheckedHoverY)
{
	_srcCheckedY[CONTROL_STATE_HOVER] = srcCheckedHoverY;
}

void CheckBox::SetSrcCheckedHoverWidth(usint srcCheckedHoverWidth)
{
	_srcCheckedWidth[CONTROL_STATE_HOVER] = srcCheckedHoverWidth;
}

void CheckBox::SetSrcCheckedHoverHeight(usint srcCheckedHoverHeight)
{
	_srcCheckedHeight[CONTROL_STATE_HOVER] = srcCheckedHoverHeight;
}

void CheckBox::SetSrcCheckedPressedX(usint srcCheckedPressedX)
{
	_srcCheckedX[CONTROL_STATE_PRESSED] = srcCheckedPressedX;
}

void CheckBox::SetSrcCheckedPressedY(usint srcCheckedPressedY)
{
	_srcCheckedY[CONTROL_STATE_PRESSED] = srcCheckedPressedY;
}

void CheckBox::SetSrcCheckedPressedWidth(usint srcCheckedPressedWidth)
{
	_srcCheckedWidth[CONTROL_STATE_PRESSED] = srcCheckedPressedWidth;
}

void CheckBox::SetSrcCheckedPressedHeight(usint srcCheckedPressedHeight)
{
	_srcCheckedHeight[CONTROL_STATE_PRESSED] = srcCheckedPressedHeight;
}

void CheckBox::SetSrcCheckedDisabledX(usint srcCheckedDisabledX)
{
	_srcCheckedX[CONTROL_STATE_DISABLED] = srcCheckedDisabledX;
}

void CheckBox::SetSrcCheckedDisabledY(usint srcCheckedDisabledY)
{
	_srcCheckedY[CONTROL_STATE_DISABLED] = srcCheckedDisabledY;
}

void CheckBox::SetSrcCheckedDisabledWidth(usint srcCheckedDisabledWidth)
{
	_srcCheckedWidth[CONTROL_STATE_DISABLED] = srcCheckedDisabledWidth;
}

void CheckBox::SetSrcCheckedDisabledHeight(usint srcCheckedDisabledHeight)
{
	_srcCheckedHeight[CONTROL_STATE_DISABLED] = srcCheckedDisabledHeight;
}

void CheckBox::Render()
{
	if (IsVisible())
	{
		if (!_checked)
		{
			XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), 
				GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(GetState()), 
				GetSrcHeight(GetState()), GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()),
				GetAlpha(GetState()));
		}
		else
		{
			XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), 
				GetHeight(), GetSrcCheckedX(GetState()), GetSrcCheckedY(GetState()), 
				GetSrcCheckedWidth(GetState()), GetSrcCheckedHeight(GetState()), GetRed(GetState()), 
				GetGreen(GetState()), GetBlue(GetState()), GetAlpha(GetState()));
		}

		Control::Render();
	}
}

};