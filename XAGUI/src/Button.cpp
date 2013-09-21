#include "XAGUI.h"

namespace XAGUI
{

Button::Button()
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcX[i] = 0;
		_srcY[i] = 0;
		_srcWidth[i] = 0;
		_srcHeight[i] = 0;
	}
}

Button::Button(tinyxml2::XMLElement* element, Control* parent)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_srcX[i] = 0;
		_srcY[i] = 0;
		_srcWidth[i] = 0;
		_srcHeight[i] = 0;
	}

	SetParent(parent);
	ParseProperties(element);
}

Button::~Button()
{
	
}

void Button::ParseProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("srcX");
	if (cstring != 0)
		SetSrcX(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcY");
	if (cstring != 0)
		SetSrcY(xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("srcWidth");
	if (cstring != 0)
		SetSrcWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcHeight");
	if (cstring != 0)
		SetSrcHeight(xaih::StrToUInt(cstring));

	cstring = element->Attribute("srcHoverX");
	(cstring != 0) ? SetSrcHoverX(xaih::StrToUInt(cstring)) : SetSrcHoverX(GetSrcX(GetState()));

	cstring = element->Attribute("srcHoverY");
	(cstring != 0) ? SetSrcHoverY(xaih::StrToUInt(cstring)) : SetSrcHoverY(GetSrcY(GetState()));

	cstring = element->Attribute("srcHoverWidth");
	(cstring != 0) ? SetSrcHoverWidth(xaih::StrToUInt(cstring)) : SetSrcHoverWidth(GetSrcWidth(GetState()));

	cstring = element->Attribute("srcHoverHeight");
	(cstring != 0) ? SetSrcHoverHeight(xaih::StrToUInt(cstring)) : SetSrcHoverHeight(GetSrcHeight(GetState()));

	cstring = element->Attribute("srcPressedX");
	(cstring != 0) ? SetSrcPressedX(xaih::StrToUInt(cstring)) : SetSrcPressedX(GetSrcX(GetState()));

	cstring = element->Attribute("srcPressedY");
	(cstring != 0) ? SetSrcPressedY(xaih::StrToUInt(cstring)) : SetSrcPressedY(GetSrcY(GetState()));

	cstring = element->Attribute("srcPressedWidth");
	(cstring != 0) ? SetSrcPressedWidth(xaih::StrToUInt(cstring)) : SetSrcPressedWidth(GetSrcWidth(GetState()));

	cstring = element->Attribute("srcPressedHeight");
	(cstring != 0) ? SetSrcPressedHeight(xaih::StrToUInt(cstring)) : SetSrcPressedHeight(GetSrcHeight(GetState()));

	cstring = element->Attribute("srcDisabledX");
	(cstring != 0) ? SetSrcDisabledX(xaih::StrToUInt(cstring)) : SetSrcDisabledX(GetSrcX(GetState()));

	cstring = element->Attribute("srcDisabledY");
	(cstring != 0) ? SetSrcDisabledY(xaih::StrToUInt(cstring)) : SetSrcDisabledY(GetSrcY(GetState()));

	cstring = element->Attribute("srcDisabledWidth");
	(cstring != 0) ? SetSrcDisabledWidth(xaih::StrToUInt(cstring)) : SetSrcDisabledWidth(GetSrcWidth(GetState()));

	cstring = element->Attribute("srcDisabledHeight");
	(cstring != 0) ? SetSrcDisabledHeight(xaih::StrToUInt(cstring)) : SetSrcDisabledHeight(GetSrcHeight(GetState()));

	Control::ParseProperties(element);
}

void Button::Render()
{
	if (IsVisible())
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
			GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(GetState()), GetSrcHeight(GetState()), 
			GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()), GetAlpha(GetState()));

		Control::Render();
	}
}

void Button::SetSrcX(usint srcX)
{
	_srcX[CONTROL_STATE_NORMAL] = srcX;
}

void Button::SetSrcY(usint srcY)
{
	_srcY[CONTROL_STATE_NORMAL] = srcY;
}

void Button::SetSrcWidth(usint srcWidth)
{
	_srcWidth[CONTROL_STATE_NORMAL] = srcWidth;
}

void Button::SetSrcHeight(usint srcHeight)
{
	_srcHeight[CONTROL_STATE_NORMAL] = srcHeight;
}

void Button::SetSrcHoverX(usint srcHoverX)
{
	_srcX[CONTROL_STATE_HOVER] = srcHoverX;
}

void Button::SetSrcHoverY(usint srcHoverY)
{
	_srcY[CONTROL_STATE_HOVER] = srcHoverY;
}

void Button::SetSrcHoverWidth(usint srcHoverWidth)
{
	_srcWidth[CONTROL_STATE_HOVER] = srcHoverWidth;
}

void Button::SetSrcHoverHeight(usint srcHoverHeight)
{
	_srcHeight[CONTROL_STATE_HOVER] = srcHoverHeight;
}

void Button::SetSrcPressedX(usint srcPressedX)
{
	_srcX[CONTROL_STATE_PRESSED] = srcPressedX;
}

void Button::SetSrcPressedY(usint srcPressedY)
{
	_srcY[CONTROL_STATE_PRESSED] = srcPressedY;
}

void Button::SetSrcPressedWidth(usint srcPressedWidth)
{
	_srcWidth[CONTROL_STATE_PRESSED] = srcPressedWidth;
}

void Button::SetSrcPressedHeight(usint srcPressedHeight)
{
	_srcHeight[CONTROL_STATE_PRESSED] = srcPressedHeight;
}

void Button::SetSrcDisabledX(usint srcDisabledX)
{
	_srcX[CONTROL_STATE_DISABLED] = srcDisabledX;
}

void Button::SetSrcDisabledY(usint srcDisabledY)
{
	_srcY[CONTROL_STATE_DISABLED] = srcDisabledY;
}

void Button::SetSrcDisabledWidth(usint srcDisabledWidth)
{
	_srcWidth[CONTROL_STATE_DISABLED] = srcDisabledWidth;
}

void Button::SetSrcDisabledHeight(usint srcDisabledHeight)
{
	_srcHeight[CONTROL_STATE_DISABLED] = srcDisabledHeight;
}

};