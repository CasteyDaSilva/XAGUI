#include "XAGUI.h"

namespace XAGUI
{

Window::Window()
{

}

Window::Window(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent)
{
	ParseProperties(element);
	Button::ParseProperties(element);
}

Window::~Window()
{

}

void Window::Render()
{
	Button::Render();
}

void Window::ParseProperties(tinyxml2::XMLElement* element)
{
	
}

};