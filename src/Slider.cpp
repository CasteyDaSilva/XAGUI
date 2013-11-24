#include "XAGUI.h"

namespace XAGUI
{

Slider::Slider()
	: _orientation(ORIENTATION_HORIZONTAL), onValueChanged(0), _markerOffsetX(0), _markerOffsetY(0), 
	_value(0), _minValue(0), _maxValue(0)
{
	_marker = new Button();
	AddChild(GetMarker());
	GetMarker()->onMouseMove.bind(this, &Slider::MarkerOnMouseMove);
	GetMarker()->onMouseButtonDown.bind(this, &Slider::MarkerOnMouseButtonDown);
}

Slider::Slider(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _orientation(ORIENTATION_HORIZONTAL), onValueChanged(0), 
	_markerOffsetX(0), _markerOffsetY(0), _value(0), _minValue(0), _maxValue(0)
{
	_marker = new Button();
	AddChild(GetMarker());
	GetMarker()->onMouseMove.bind(this, &Slider::MarkerOnMouseMove);
	GetMarker()->onMouseButtonDown.bind(this, &Slider::MarkerOnMouseButtonDown);
	ReadProperties(element);
}

Slider::~Slider()
{
	
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
		else if (*string.rbegin() == 'r')
		{
			GetMarker()->SetRatioWidth(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
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
		else if (*string.rbegin() == 'r')
		{
			GetMarker()->SetRatioHeight(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
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
	
	cstring = element->Attribute("mhSrcX");
	if (cstring != 0)
	{
		GetMarker()->SetSrcX(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcX(CONTROL_STATE_HOVER, GetMarker()->GetSrcX(CONTROL_STATE_NORMAL));
	}

	cstring = element->Attribute("mhSrcY");
	if (cstring != 0)
	{
		GetMarker()->SetSrcY(CONTROL_STATE_HOVER, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcY(CONTROL_STATE_HOVER, GetMarker()->GetSrcY(CONTROL_STATE_NORMAL));
	}

	cstring = element->Attribute("maSrcX");
	if (cstring != 0)
	{
		GetMarker()->SetSrcX(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcX(CONTROL_STATE_ACTIVE, GetMarker()->GetSrcX(CONTROL_STATE_NORMAL));
	}

	cstring = element->Attribute("maSrcY");
	if (cstring != 0)
	{
		GetMarker()->SetSrcY(CONTROL_STATE_ACTIVE, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcY(CONTROL_STATE_ACTIVE, GetMarker()->GetSrcY(CONTROL_STATE_NORMAL));
	}

	cstring = element->Attribute("mdSrcX");
	if (cstring != 0)
	{
		GetMarker()->SetSrcX(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcX(CONTROL_STATE_DISABLED, GetMarker()->GetSrcX(CONTROL_STATE_NORMAL));
	}

	cstring = element->Attribute("mdSrcY");
	if (cstring != 0)
	{
		GetMarker()->SetSrcY(CONTROL_STATE_DISABLED, xaih::StrToUInt(cstring));
	}
	else
	{
		GetMarker()->SetSrcY(CONTROL_STATE_DISABLED, GetMarker()->GetSrcY(CONTROL_STATE_NORMAL));
	}

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
		value = GetMinValue();
	}
	else if (value > GetMaxValue())
	{
		value = GetMaxValue();
	}

	_value = value;

	(onValueChanged != 0) ? onValueChanged(this) : OnValueChangedEvent();

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
}

Control* Slider::MouseMoveEvent(int x, int y)
{
	Control* control = Control::MouseMoveEvent(x, y);
	if (control == this && IsPressed())
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
	return control;
}

Control* Slider::MouseButtonDownEvent(int x, int y, uchar button)
{
	Control* control = Control::MouseButtonDownEvent(x, y, button);
	if (control == this)
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
	return control;
}

void Slider::MarkerOnMouseMove(Control* control, int x, int y)
{
	if (GetMarker()->IsPressed())
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

void Slider::MarkerOnMouseButtonDown(Control* control, int x, int y, uchar button)
{
	if (GetOrientation() == ORIENTATION_VERTICAL)
	{
		SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / static_cast<float>(GetHeight() / 
			static_cast<float>(y - GetAbsY()))));
	}
	else
	{
		SetValue(static_cast<int>((GetMaxValue() - GetMinValue()) / static_cast<float>(GetWidth() / 
			static_cast<float>(x - GetAbsX()))));
	}
}

void Slider::OnValueChangedEvent()
{

}

};