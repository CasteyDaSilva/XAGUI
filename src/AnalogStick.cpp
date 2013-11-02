#include "XAGUI.h"

namespace XAGUI
{

AnalogStick::AnalogStick()
	: _stickX(0), _stickY(0), _valueX(0), _valueY(0), _pressed(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_stickSrcX[i] = 0;
		_stickSrcY[i] = 0;
	}
}

AnalogStick::AnalogStick(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _stickX(0), _stickY(0), _valueX(0), _valueY(0), _pressed(false)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		_stickSrcX[i] = 0;
		_stickSrcY[i] = 0;
	}

	ReadProperties(element);
}

AnalogStick::~AnalogStick()
{

}

void AnalogStick::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("sSrcX");
	if (cstring != 0)
		SetStickSrcX(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("sSrcY");
	if (cstring != 0)
		SetStickSrcY(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("shSrcX");
	if (cstring != 0) 
	{ 
		SetStickSrcX(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcX(CONTROL_STATE_HOVER, GetStickSrcX(GetState()));
	}

	cstring = element->Attribute("shSrcY");
	if (cstring != 0) 
	{ 
		SetStickSrcY(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcY(CONTROL_STATE_HOVER, GetStickSrcY(GetState()));
	}
	
	cstring = element->Attribute("saSrcX");
	if (cstring != 0) 
	{ 
		SetStickSrcX(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcX(CONTROL_STATE_ACTIVE, GetStickSrcX(GetState()));
	}

	cstring = element->Attribute("saSrcY");
	if (cstring != 0) 
	{ 
		SetStickSrcY(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcY(CONTROL_STATE_ACTIVE, GetStickSrcY(GetState()));
	}

	cstring = element->Attribute("sdSrcX");
	if (cstring != 0) 
	{ 
		SetStickSrcX(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcX(CONTROL_STATE_DISABLED, GetStickSrcX(GetState()));
	}

	cstring = element->Attribute("sdSrcY");
	if (cstring != 0) 
	{ 
		SetStickSrcY(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{ 
		SetStickSrcY(CONTROL_STATE_DISABLED, GetStickSrcY(GetState()));
	}

	ResetStick();
}

void AnalogStick::Render()
{
	if (IsVisible())
	{
		Button::Render();

		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), _stickX, _stickY, GetWidth(), 
			GetHeight(), GetStickSrcX(GetState()), GetStickSrcY(GetState()), GetSrcWidth(), 
			GetSrcHeight(), GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()), 
			GetAlpha(GetState()));
	}
}

void AnalogStick::ResetStick()
{
	SetStickX(GetAbsX());
	SetStickY(GetAbsY());
}

void AnalogStick::SetStickX(sint stickX)
{
	if (stickX < GetAbsX() - ceil(GetWidth() / 4.0f))
	{
		_stickX = GetAbsX() - static_cast<sint>(ceil(GetWidth() / 4.0f));
		_valueX = -1.0f;
	}
	else if (stickX > GetAbsX() + ceil(GetWidth() / 4.0f))
	{
		_stickX = GetAbsX() + static_cast<sint>(ceil(GetWidth() / 4.0f));
		_valueX = 1.0f;
	}
	else 
	{
		_stickX = stickX;
		_valueX = (GetStickX() - GetAbsX()) / xaih::Round((GetWidth() / 4.0f));
	}
}

void AnalogStick::SetStickY(sint stickY)
{
	if (stickY < GetAbsY() - ceil(GetHeight() / 4.0f))
	{
		_stickY = GetAbsY() - static_cast<sint>(ceil(GetHeight() / 4.0f));
		_valueY = 1.0f;
	}
	else if (stickY > GetAbsY() + ceil(GetHeight() / 4.0f))
	{
		_stickY = GetAbsY() + static_cast<sint>(ceil(GetHeight() / 4.0f));
		_valueY = -1.0f;
	}
	else 
	{
		_stickY = stickY;
		_valueY = -(GetStickY() - GetAbsY()) / xaih::Round((GetHeight() / 4.0f));
	}
}

void AnalogStick::MouseMoveEvent(int x, int y)
{
	if (_pressed)
	{
		if (x < GetAbsX() + GetWidth() / 2)
		{
			SetStickX(x - GetWidth() / 2);
		}
		else
		{
			SetStickX(x - GetWidth() / 2);
		}

		if (y < GetAbsY() + GetHeight() / 2)
		{
			SetStickY(y - GetHeight() / 2);
		}
		else
		{
			SetStickY(y - GetHeight() / 2);
		}
	}
}

bool AnalogStick::MouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	if (button == MOUSE_BUTTON_LEFT && down)
	{
		if (xaih::IsPointInRectangle(static_cast<float>(x), static_cast<float>(y), 
			static_cast<float>(GetAbsX()), static_cast<float>(GetAbsY()), GetWidth(), GetHeight()))
		{
			if (x < GetAbsX() + GetWidth() / 2)
			{
				SetStickX(x - GetWidth() / 2);
			}
			else
			{
				SetStickX(x - GetWidth() / 2);
			}

			if (y < GetAbsY() + GetHeight() / 2)
			{
				SetStickY(y - GetHeight() / 2);
			}
			else
			{
				SetStickY(y - GetHeight() / 2);
			}

			_pressed = true;
		}
	}
	else
	{
		_pressed = false;
		ResetStick();
	}

	return IsConsumeMouseEvents();
}

};