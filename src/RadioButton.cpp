#include "XAGUI.h"

namespace XAGUI
{

RadioButton::RadioButton()
{

}

RadioButton::RadioButton(tinyxml2::XMLElement* element, Control* parent)
	: CheckBox(element, parent)
{

}

RadioButton::~RadioButton()
{

}

void RadioButton::OnClickEvent()
{
	if (!IsChecked()) 
		SetChecked(true); 
}

};