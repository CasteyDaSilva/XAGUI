#include "XAGUI.h"

namespace XAGUI
{

PictureBox::PictureBox()
	: _image(0)
{

}

PictureBox::PictureBox(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _image(0)
{
	ReadProperties(element);
}

PictureBox::~PictureBox()
{
	
}

void PictureBox::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("image");
	if (cstring != 0)
		SetImage(XAGUI::GetRenderer()->GetTexture(cstring));
}

void PictureBox::Render()
{
	if (GetImage() != 0 && IsVisible())
	{
		XAGUI::GetRenderer()->Render(GetImage(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
			GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
			GetColor(GetState()));
			
		Control::Render();
	}
}

void PictureBox::DeleteTexture()
{
	SAFE_DELETE(_image);
}

};