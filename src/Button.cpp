#include "XAGUI.h"

namespace XAGUI
{

Button::Button()
	: _srcWidth(0), _srcHeight(0)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcX[i] = 0;
		_srcY[i] = 0;
	}
}

Button::Button(tinyxml2::XMLElement* element, Control* parent)
	: _srcWidth(0), _srcHeight(0)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcX[i] = 0;
		_srcY[i] = 0;
	}

	SetParent(parent);
	ReadProperties(element);
}

Button::~Button()
{
	
}

void Button::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("srcX");
	if (cstring != 0)
		SetSrcX(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcY");
	if (cstring != 0)
		SetSrcY(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("srcW");
	if (cstring != 0)
		SetSrcWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcH");
	if (cstring != 0)
		SetSrcHeight(xaih::StrToUInt(cstring));

	cstring = element->Attribute("hSrcX");
	if (cstring != 0) 
	{
		SetSrcX(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{
		SetSrcX(CONTROL_STATE_HOVER, GetSrcX(GetState()));
	}

	cstring = element->Attribute("hSrcY");
	if (cstring != 0) 
	{
		SetSrcY(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcY(CONTROL_STATE_HOVER, GetSrcY(GetState()));
	}

	cstring = element->Attribute("aSrcX");
	if (cstring != 0) 
	{
		SetSrcX(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring)); 
	}
	else
	{ 
		SetSrcX(CONTROL_STATE_ACTIVE, GetSrcX(GetState()));
	}

	cstring = element->Attribute("aSrcY");
	if (cstring != 0) 
	{
		SetSrcY(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring)); 
	}
	else
	{ 
		SetSrcY(CONTROL_STATE_ACTIVE, GetSrcY(GetState()));
	}

	cstring = element->Attribute("dSrcX");
	if (cstring != 0) 
	{
		SetSrcX(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcX(CONTROL_STATE_DISABLED, GetSrcX(GetState()));
	}

	cstring = element->Attribute("dSrcY");
	if (cstring != 0) 
	{
		SetSrcY(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetSrcY(CONTROL_STATE_DISABLED, GetSrcY(GetState()));
	}

	Control::ReadProperties(element);
}

void Button::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
			GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
			GetColor(GetState()));
		Control::Render();
	}
}

void Button::SetSrcX(ControlState controlState, usint srcX) 
{ 
	if (controlState == CONTROL_STATE_COUNT)
	{
		for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
			_srcX[i] = srcX;
	}
	else
	{
		_srcX[controlState] = srcX; 
	}
}

void Button::SetSrcY(ControlState controlState, usint srcY) 
{ 
	if (controlState == CONTROL_STATE_COUNT)
	{
		for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
			_srcY[i] = srcY;
	}
	else
	{
		_srcY[controlState] = srcY; 
	}
}

};