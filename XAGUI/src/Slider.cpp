#include "XAGUI.h"

namespace XAGUI
{

Slider::Slider()
	: _value(0), _minValue(0), _maxValue(0), _markerSrcX(0), _markerSrcY(0), _markerSrcWidth(0), 
	_markerSrcHeight(0)
{

}

Slider::Slider(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _value(0), _minValue(0), _maxValue(0), _markerSrcX(0), _markerSrcY(0), 
	_markerSrcWidth(0), _markerSrcHeight(0)
{
	ParseProperties(element);
	Button::ParseProperties(element);
}

Slider::~Slider()
{

}

void Slider::Render()
{
	if (IsVisible())
	{
		Button::Render();
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetMarkerSrcWidth(), 
			GetMarkerSrcHeight(), GetMarkerSrcX(), GetMarkerSrcY(), GetMarkerSrcWidth(), 
			GetMarkerSrcHeight(), GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()), 
			GetAlpha(GetState()));
	}
}

void Slider::ParseProperties(tinyxml2::XMLElement* element)
{
	
}

void Slider::SetMarkerSrcX(usint markerSrcX)
{
	_markerSrcX = markerSrcX;
}

void Slider::SetMarkerSrcY(usint markerSrcY)
{
	_markerSrcY = markerSrcY;
}

void Slider::SetMarkerSrcWidth(usint markerSrcWidth)
{
	_markerSrcWidth = markerSrcWidth;
}

void Slider::SetMarkerSrcHeight(usint markerSrcHeight)
{
	_markerSrcHeight = markerSrcHeight;
}

};