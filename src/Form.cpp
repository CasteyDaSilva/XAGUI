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
	PictureBox::SetImage(XAGUI::GetRenderer()->GetTexture(document.RootElement()->Attribute("skin")));
	PictureBox::ReadProperties(document.RootElement());
	ParseChildren(document.RootElement());
	
	return result;
}

void Form::Render()
{
	XAGUI::SetSkin(GetSkin());
	PictureBox::Render();
}

void Form::MouseMoveEvent(int x, int y)
{
	Control::MouseMoveEvent(x, y);
	Control::MouseEvent(x, y, MOUSE_BUTTON_COUNT, false);
}

bool Form::MouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	Control::MouseButtonEvent(x, y, button, down);
	return Control::MouseEvent(x, y, button, down);
}

};