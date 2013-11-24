#include "XAGUI.h"

namespace XAGUI
{

Window::Window()
	: _dragX(0), _dragY(0)
{

}

Window::Window(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _dragX(0), _dragY(0)
{
	ReadProperties(element);
}

Window::~Window()
{

}

void Window::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("draggable");
	if (cstring != 0)
		SetDraggable(xaih::StrToBool(cstring));

	cstring = element->Attribute("dragAreaX");
	// if (cstring != 0)

	cstring = element->Attribute("dragAreaY");
	// if (cstring != 0)

	cstring = element->Attribute("dragAreaW");
	// if (cstring != 0)

	cstring = element->Attribute("dragAreaH");
	// if (cstring != 0)
}

void Window::Render()
{
	Button::Render();
}

Control* Window::MouseMoveEvent(int x, int y)
{
	Control* control = Control::MouseMoveEvent(x, y);
	if (control == this && IsDraggable() && IsPressed() /* same as IsActive() */)
	{
		SetX(x - GetDragX());
		SetY(y - GetDragY());
	}
	return control;
}

Control* Window::MouseButtonDownEvent(int x, int y, uchar button)
{
	Control* control = Control::MouseButtonDownEvent(x, y, button);
	if (control == this && IsDraggable() && 
		xaih::IsPointInRectangle(x, y, GetAbsX(), GetAbsY(), GetWidth(), GetHeight()))
	{
		SetDragX(x - GetAbsX() + GetAlignmentX());
		SetDragY(y - GetAbsY() + GetAlignmentY());	
	}
	return control;
}

};