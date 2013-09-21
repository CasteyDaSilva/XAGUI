#include "XAGUI.h"

namespace XAGUI
{

StaticImage::StaticImage()
	: _image(0)
{

}

StaticImage::StaticImage(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _image(0)
{
	ParseProperties(element);
}

StaticImage::~StaticImage()
{
	
}

void StaticImage::ParseProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("image");
	if (cstring != 0)
		SetImage(XAGUI::GetRenderer()->GetTexture(cstring));

	Button::ParseProperties(element);
}

void StaticImage::DeleteTexture()
{
	SAFE_DELETE(_image);
}

void StaticImage::SetImage(Texture* image)
{
	_image = image;
}

void StaticImage::Render()
{
	if (_image != 0 && IsVisible())
	{
		XAGUI::GetRenderer()->Render(GetImage(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
			GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(GetState()), GetSrcHeight(GetState()), 
			GetRed(GetState()), GetGreen(GetState()), GetBlue(GetState()), GetAlpha(GetState()));
			
		Control::Render();
	}
}

};