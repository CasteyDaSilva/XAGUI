#include "XAGUI.h"

namespace XAGUI
{

TextBox::TextBox()
	: _caretPosition(0), _caretPositionX(0), _caretPositionY(0), _caretSrcX(0), _caretSrcY(0),
	_caretSrcWidth(0), _caretSrcHeight(0)
{
	_label = new Label();
}

TextBox::TextBox(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _caretPosition(0), _caretPositionX(0), _caretPositionY(0), _caretSrcX(0), 
	_caretSrcY(0), _caretSrcWidth(0), _caretSrcHeight(0)
{
	_label = new Label();
	ReadProperties(element);
}

TextBox::~TextBox()
{
	delete _label;
}

void TextBox::ReadProperties(tinyxml2::XMLElement* element)
{
	_label->SetParent(this);
	_label->ReadProperties(element);

	bool textCenter = element->BoolAttribute("tCenter");

	cchar* cstring = element->Attribute("tX");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == 'r')
		{
			_label->SetRatioX(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
		}
		else
		{
			_label->SetX(xaih::StrToInt(string.c_str()));
		}
	}

	cstring = element->Attribute("tY");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == 'r')
		{
			_label->SetRatioY(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
		}
		else
		{
			_label->SetY(xaih::StrToInt(string.c_str()));
		}
	}
	
	cstring = element->Attribute("tColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColor(CONTROL_STATE_NORMAL, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("htColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColor(CONTROL_STATE_HOVER, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("atColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColor(CONTROL_STATE_ACTIVE, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("dtColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColor(CONTROL_STATE_DISABLED, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("cSrcX");
	if (cstring != 0)
		SetCaretSrcX(xaih::StrToUInt(cstring));

	cstring = element->Attribute("cSrcY");
	if (cstring != 0)
		SetCaretSrcY(xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("cSrcW");
	if (cstring != 0)
		SetCaretSrcWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("cSrcH");
	if (cstring != 0)
		SetCaretSrcHeight(xaih::StrToUInt(cstring));
}

void TextBox::Render()
{
	if (IsVisible())
	{
		Button::Render();
		_label->Render();
	
		if (Control::GetFocusedControl() == this)
		{
			XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetCaretPositionX(), GetCaretPositionY(), 
				GetCaretSrcWidth(), _label->GetHeight(), GetCaretSrcX(), GetCaretSrcY(), 
				GetCaretSrcWidth(), GetCaretSrcHeight(), _label->GetColor(GetState()));
		}
	}
}

void TextBox::InsertText(cchar* text, int position)
{
	_label->GetStaticText()->GetPointerToString()->insert(position, text);
	SetText(_label->GetStaticText()->Get());
	SetCaretPosition(position + strlen(text));
}

void TextBox::RemoveCharacter(int position)
{
	if (GetCaretPosition() > 0 && _label->GetStaticText()->GetLength() > 0)
	{
		_label->GetStaticText()->GetPointerToString()->erase(position, 1);
		SetText(_label->GetStaticText()->Get());
		SetCaretPosition(position);
	}
}

void TextBox::SetText(cchar* text) 
{ 
	_label->SetText(text); 
	SetCaretPosition(_label->GetStaticText()->GetLength());
}

void TextBox::SetCaretPosition(int position)
{
	if (position < 0 || static_cast<uint>(position) > _label->GetStaticText()->GetLength()) return;

	_caretPosition = position;
	_caretPositionX = _label->GetAbsX() + _label->GetStaticText()->GetFont()->GetTextWidth(
		_label->GetStaticText()->GetPointerToString()->substr(0, position).c_str());
	_caretPositionY = _label->GetAbsY();
}

Control* TextBox::MouseButtonDownEvent(int x, int y, uchar button)
{
	Control* control = Control::MouseButtonDownEvent(x, y, button);
	if (control == this)
	{
		if (xaih::IsPointInRectangle(x, y, GetAbsX(), GetAbsY(), GetWidth(), GetHeight()))
		{
			int characterX = _label->GetAbsX();
			int characterWidth = 0;

			for (uint i = 0; i < _label->GetStaticText()->GetLength(); i++)
			{
				characterWidth = _label->GetStaticText()->GetFont()->GetTextWidth(
					_label->GetStaticText()->GetPointerToString()->substr(i, 1).c_str());

				if(x >= characterX && x <= characterX + characterWidth)
				{
					SetCaretPosition(i);
					break;
				}

				characterX += characterWidth;
			}

			if (x > characterX + characterWidth)
				SetCaretPosition(_label->GetStaticText()->GetLength());
		}
	}
	return control;
}

void TextBox::OnKeyDownEvent(SDL_Scancode key)
{
	switch (key)
	{
		case SDL_SCANCODE_LEFT:
			SetCaretPosition(GetCaretPosition() - 1);
			break;

		case SDL_SCANCODE_RIGHT:
			SetCaretPosition(GetCaretPosition() + 1);
			break;

		case SDL_SCANCODE_BACKSPACE:
			RemoveCharacter(GetCaretPosition() - 1);
			break;
	}
}

bool TextBox::TextInputEvent(std::string text)
{
	InsertText(text.c_str(), GetCaretPosition());
	return Control::IsConsumeKeyboardEvents();
}

void TextBox::OnGotFocus()
{
	XAGUI::StartTextInput();
}

void TextBox::OnLostFocus()
{
	XAGUI::StopTextInput();
}

};