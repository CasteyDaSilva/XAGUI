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
			GetSrcHeight(), GetColor(GetState()));
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
		SetValueX(-1.0f);
	}
	else if (stickX > GetAbsX() + ceil(GetWidth() / 4.0f))
	{
		_stickX = GetAbsX() + static_cast<sint>(ceil(GetWidth() / 4.0f));
		SetValueX(1.0f);
	}
	else 
	{
		_stickX = stickX;
		SetValueX((GetStickX() - GetAbsX()) / xaih::Round((GetWidth() / 4.0f)));
	}
}

void AnalogStick::SetStickY(sint stickY)
{
	if (stickY < GetAbsY() - ceil(GetHeight() / 4.0f))
	{
		_stickY = GetAbsY() - static_cast<sint>(ceil(GetHeight() / 4.0f));
		SetValueY(1.0f);
	}
	else if (stickY > GetAbsY() + ceil(GetHeight() / 4.0f))
	{
		_stickY = GetAbsY() + static_cast<sint>(ceil(GetHeight() / 4.0f));
		SetValueY(-1.0f);
	}
	else 
	{
		_stickY = stickY;
		SetValueY(-(GetStickY() - GetAbsY()) / xaih::Round((GetHeight() / 4.0f)));
	}
}

void AnalogStick::SetValueX(float valueX)
{
	_valueX = valueX;
	(onValueChanged != 0) ? onValueChanged(this) : OnValueChangedEvent();
}
void
	AnalogStick::SetValueY(float valueY)
{
	_valueY = valueY;
	(onValueChanged != 0) ? onValueChanged(this) : OnValueChangedEvent();
}

Control* AnalogStick::MouseMoveEvent(int x, int y)
{
	Control* control = Control::MouseMoveEvent(x, y);
	if (IsPressed())
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
	return control;
}

Control* AnalogStick::MouseButtonDownEvent(int x, int y, uchar button)
{
	Control* control = Control::MouseButtonDownEvent(x, y, button);
	if (control == this)
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
	return control;
}

void AnalogStick::MouseButtonUpEvent(int x, int y, uchar button)
{
	Control::MouseButtonUpEvent(x, y, button);
	if (button == SDL_BUTTON_LEFT)
		ResetStick();
}

void AnalogStick::OnValueChangedEvent()
{

}

};