#include "XAGUI.h"

namespace XAGUI
{

MultilineTextBox::MultilineTextBox()
{

}

MultilineTextBox::MultilineTextBox(tinyxml2::XMLElement* element, Control* parent)
	: TextBox(element, parent)
{
	ReadProperties(element);
}

MultilineTextBox::~MultilineTextBox()
{

}

void MultilineTextBox::ReadProperties(tinyxml2::XMLElement* element)
{

}

};