#include "XAGUI.h"

namespace XAGUI
{

Window::Window()
{

}

Window::Window(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent)
{
	ReadProperties(element);
}

Window::~Window()
{

}

void Window::ReadProperties(tinyxml2::XMLElement* element)
{
	
}

void Window::Render()
{
	Button::Render();
}

};