#include "XAGUI.h"

namespace XAGUI
{

Slider::Slider()
	: _orientation(ORIENTATION_HORIZONTAL), onValueChanged(0), _markerOffsetX(0), _markerOffsetY(0), 
	_value(0), _minValue(0), _maxValue(0), _pressed(false)
{
	_marker = new Button();
}

Slider::Slider(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _orientation(ORIENTATION_HORIZONTAL), onValueChanged(0), 
	_markerOffsetX(0), _markerOffsetY(0), _value(0), _minValue(0), _maxValue(0), _pressed(false)
{
	_marker = new Button();
	ReadProperties(element);
}

Slider::~Slider()
{
	delete _marker;
}

void Slider::Render()
{
	if (IsVisible())
	{
		Button::Render();
		GetMarker()->Render();
	}
}

void Slider::ReadProperties(tinyxml2::XMLElement* element)
{
	GetMarker()->SetParent(this);

	cchar* cstring = element->Attribute("orientation");
	if (cstring != 0)
	{
		if (strcmp(cstring, "VERTICAL") == 0)
		{
			SetOrientation(ORIENTATION_VERTICAL);
		}
		else
		{
			SetOrientation(ORIENTATION_HORIZONTAL);
		}
	}

	cstring = element->Attribute("mOffsetX");
	if (cstring != 0)
		SetMarkerOffsetX(xaih::StrToInt(cstring));

	cstring = element->Attribute("mOffsetY");
	if (cstring != 0)
		SetMarkerOffsetY(xaih::StrToInt(cstring));
	
	cstring = element->Attribute("mW");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (string.compare("AUTO") == 0)
		{
			GetMarker()->SetAutoWidth();
		}
		else if (*string.rbegin() == 'p')
		{
			GetMarker()->SetPermilWidth(xaih::StrToUInt(xaih::ParseString(string, "p").c_str()));
		}
		else
		{
			GetMarker()->SetWidth(xaih::StrToUInt(string.c_str()));
		}
	}
	else
	{
		GetMarker()->SetWidth(0);
	}

	cstring = element->Attribute("mH");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (string.compare("AUTO") == 0)
		{
			GetMarker()->SetAutoHeight();
		}
		else if (*string.rbegin() == 'p')
		{
			GetMarker()->SetPermilHeight(xaih::StrToUInt(xaih::ParseString(string, "p").c_str()));
		}
		else
		{
			GetMarker()->SetHeight(xaih::StrToUInt(string.c_str()));
		}
	}
	else
	{
		GetMarker()->SetHeight(0);
	}

	cstring = element->Attribute("mSrcX");
	if (cstring != 0)
		GetMarker()->SetSrcX(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));

	cstring = element->Attribute("mSrcY");
	if (cstring != 0)
		GetMarker()->SetSrcY(CONTROL_STATE_NORMAL, xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("mSrcW");
	if (cstring != 0)
		GetMarker()->SetSrcWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("mSrcH");
	if (cstring != 0)
		GetMarker()->SetSrcHeight(xaih::StrToUInt(cstring));

	cstring = element->Attribute("minValue");
	if (cstring != 0)
		SetMinValue(xaih::StrToInt(cstring));
	
	cstring = element->Attribute("maxValue");
	if (cstring != 0)
		SetMaxValue(xaih::StrToInt(cstring));

	cstring = element->Attribute("value");
	if (cstring != 0)
		SetValue(xaih::StrToInt(cstring));
}

void Slider::SetMarkerOffsetX(sint markerOffsetX)
{
	_markerOffsetX = markerOffsetX;
	SetValue(GetValue());
}

void Slider::SetMarkerOffsetY(sint markerOffsetY)
{
	_markerOffsetY = markerOffsetY;
	SetValue(GetValue());
}

void Slider::SetMinValue(int minValue) 
{ 
	_minValue = minValue; 
	SetValue(GetValue());
}

void Slider::SetMaxValue(int maxValue) 
{ 
	_maxValue = maxValue; 
	SetValue(GetValue());
}

void Slider::SetValue(int value) 
{ 
	if (value < GetMinValue())
	{
		_value = GetMinValue();
	}
	else if (value > GetMaxValue())
	{
		_value = GetMaxValue();
	}
	else
	{
		_value = value;
	}

	if (GetOrientation() == ORIENTATION_VERTICAL)
	{
		GetMarker()->SetX(GetMarkerOffsetX());
		GetMarker()->SetY(static_cast<sint>(GetMarkerOffsetY() + GetHeight() / 
			((GetMaxValue() - GetMinValue()) / static_cast<float>(GetValue())) - GetMarker()->GetHeight() 
			/ 2.0f));
	}
	else
	{
		GetMarker()->SetX(static_cast<sint>(GetMarkerOffsetX() + GetWidth() / 
			((GetMaxValue() - GetMinValue()) / static_cast<float>(GetValue())) - GetMarker()->GetWidth() 
			/ 2.0f));
		GetMarker()->SetY(GetMarkerOffsetY());
	}

	if (onValueChanged != 0) 
		onValueChanged(this, GetValue());
}

void Slider::MouseMoveEvent(int x, int y)
{
	if (_pressed)
	{
		if (GetOrientation() == ORIENTATION_VERTICAL)
		{
			SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / 
				static_cast<float>(GetHeight() / static_cast<float>(y - GetAbsY()))));
		}
		else
		{
			SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / 
				static_cast<float>(GetWidth() / static_cast<float>(x - GetAbsX()))));
		}
	}
}

bool Slider::MouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	if (button == MOUSE_BUTTON_LEFT && down)
	{
		if (xaih::IsPointInRectangle(static_cast<float>(x), static_cast<float>(y), 
			static_cast<float>(GetAbsX()), static_cast<float>(GetAbsY()), GetWidth(), GetHeight()))
		{
			if (GetOrientation() == ORIENTATION_VERTICAL)
			{
				SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / 
					static_cast<float>(GetHeight() / static_cast<float>(y - GetAbsY()))));
			}
			else
			{
				SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / 
					static_cast<float>(GetWidth() / static_cast<float>(x - GetAbsX()))));
			}

			_pressed = true;
		}
	}
	else
	{
		_pressed = false;
	}

	return IsConsumeMouseEvents();
}

};