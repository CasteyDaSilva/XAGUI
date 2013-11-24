#include "XAGUI.h"

namespace XAGUI
{

ControlBase::ControlBase()
{

}

ControlBase::~ControlBase()
{

}

void ControlBase::ReadProperties(tinyxml2::XMLElement* element)
{
	SetID(element->Attribute("id"));

	if (strcmp(element->Name(), "form") != 0) 
		_type = element->Attribute("type"); 
}

};