#include "XAGUI.h"

namespace XAGUI
{

Form::Form()
{
	_type = "form";
}

Form::~Form()
{
	PictureBox::DeleteTexture();
}

tinyxml2::XMLError Form::Load(cchar* file)
{
	tinyxml2::XMLDocument document;
	tinyxml2::XMLError result = document.LoadFile(file);
	if (result != 0) return result;

	Button::ReadProperties(document.RootElement());
	SetImage(XAGUI::GetRenderer()->GetTexture(document.RootElement()->Attribute("skin")));
	ParseChildren(document.RootElement());
	
	return result;
}

tinyxml2::XMLError Form::LoadFromMemory(cchar* buffer)
{
	tinyxml2::XMLDocument document;
	tinyxml2::XMLError result = document.Parse(buffer);
	if (result != 0) return result;

	Button::ReadProperties(document.RootElement());
	SetImage(XAGUI::GetRenderer()->GetTexture(document.RootElement()->Attribute("skin")));
	ParseChildren(document.RootElement());
	
	return result;
}

void Form::Render()
{
	XAGUI::SetSkin(GetSkin());
	PictureBox::Render();
}

};