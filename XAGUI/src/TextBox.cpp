#include "XAGUI.h"

namespace XAGUI
{

TextBox::TextBox()
	: _label(0), _caretPosition(0), _caretPositionX(0), _caretPositionY(0), _caretSrcX(0), _caretSrcY(0),
	_caretSrcWidth(0), _caretSrcHeight(0)
{
	_label = new Label();
}

TextBox::TextBox(tinyxml2::XMLElement* element, Control* parent)
	: Button(element, parent), _label(0), _caretPosition(0), _caretPositionX(0), _caretPositionY(0), 
	_caretSrcX(0), _caretSrcY(0), _caretSrcWidth(0), _caretSrcHeight(0)
{
	_label = new Label();
	ParseProperties(element);
}

TextBox::~TextBox()
{
	delete _label;
}

void TextBox::ParseProperties(tinyxml2::XMLElement* element)
{
	_label->SetParent(this);
	_label->ParseProperties(element);

	bool textCenter = element->BoolAttribute("textCenter");

	cchar* cstring = element->Attribute("textX");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == 'p')
		{
			_label->SetPermilX(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), textCenter);
		}
		else
		{
			_label->SetX(xaih::StrToInt(string.c_str()));
		}
	}

	cstring = element->Attribute("textY");
	if (cstring != 0)
	{
		std::string string = cstring;
		if (*string.rbegin() == 'p')
		{
			_label->SetPermilY(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), textCenter);
		}
		else
		{
			_label->SetY(xaih::StrToInt(string.c_str()));
		}
	}
	
	cstring = element->Attribute("textColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColor((color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, 
			color & 0xff);
		}
	}

	cstring = element->Attribute("textColorHover");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColorHover((color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, 
			color & 0xff);
		}
	}

	cstring = element->Attribute("textColorPressed");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColorPressed((color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, 
			color & 0xff);
		}
	}

	cstring = element->Attribute("textColorDisabled");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			_label->SetColorDisabled((color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, 
			color & 0xff);
		}
	}

	cstring = element->Attribute("caretSrcX");
	if (cstring != 0)
		SetCaretSrcX(xaih::StrToUInt(cstring));

	cstring = element->Attribute("caretSrcY");
	if (cstring != 0)
		SetCaretSrcY(xaih::StrToUInt(cstring));
	
	cstring = element->Attribute("caretSrcWidth");
	if (cstring != 0)
		SetCaretSrcWidth(xaih::StrToUInt(cstring));

	cstring = element->Attribute("caretSrcHeight");
	if (cstring != 0)
		SetCaretSrcHeight(xaih::StrToUInt(cstring));

	Button::ParseProperties(element);
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
				GetCaretSrcWidth(), GetCaretSrcHeight(), _label->GetRed(GetState()), 
				_label->GetGreen(GetState()), _label->GetBlue(GetState()), _label->GetAlpha(GetState()));
		}
	}
}

void TextBox::RemoveCharacter(int position)
{
	if (GetCaretPosition() > 0 && _label->GetText()->GetLength() > 0)
	{
		_label->GetText()->GetPtrStdStr()->erase(position, 1);
		_label->SetText(_label->GetText()->Get());
		SetCaretPosition(position);
	}
}

void TextBox::KeyEvent(Key key, bool down)
{
	if (down)
	{
		switch (key)
		{
			case KEY_LEFT_ARROW:
				SetCaretPosition(GetCaretPosition() - 1);
				break;

			case KEY_RIGHT_ARROW:
				SetCaretPosition(GetCaretPosition() + 1);
				break;

			case KEY_BACKSPACE:
				RemoveCharacter(GetCaretPosition() - 1);
				break;
		}
	}
}

void TextBox::TextInputEvent(std::string text)
{
	_label->GetText()->GetPtrStdStr()->insert(GetCaretPosition(), text.c_str());
	_label->SetText(_label->GetText()->Get());
	SetCaretPosition(GetCaretPosition() + text.length());
}

void TextBox::SetText(cchar* text)
{
	_label->SetText(text);
}

void TextBox::SetCaretPosition(int position)
{
	if (position < 0 || static_cast<uint>(position) > _label->GetText()->GetLength()) 
		return;

	_caretPosition = position;
	_caretPositionX = _label->GetAbsX() + _label->GetText()->GetFont()->GetTextWidth(
		_label->GetText()->GetPtrStdStr()->substr(0, position).c_str());
	_caretPositionY = _label->GetAbsY();
}

void TextBox::SetCaretSrcX(usint caretSrcX)
{
	_caretSrcX = caretSrcX;
}

void TextBox::SetCaretSrcY(usint caretSrcY)
{
	_caretSrcY = caretSrcY;
}

void TextBox::SetCaretSrcWidth(usint caretSrcWidth)
{
	_caretSrcWidth = caretSrcWidth;
}

void TextBox::SetCaretSrcHeight(usint caretSrcHeight)
{
	_caretSrcHeight = caretSrcHeight;
}

void TextBox::OnMouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	if (Control::GetFocusedControl() == this && button == MOUSE_BUTTON_LEFT && down)
	{
		int characterX = _label->GetAbsX();
		int characterWidth = 0;

		for (uint i = 0; i < _label->GetText()->GetLength(); i++)
		{
			characterWidth = _label->GetText()->GetFont()->GetTextWidth(
				_label->GetText()->GetPtrStdStr()->substr(i, 1).c_str());

			if(x >= characterX && x <= characterX + characterWidth)
			{
				SetCaretPosition(i);
				break;
			}

			characterX += characterWidth;
		}
	}
}

void TextBox::OnGetFocus()
{
	SetCaretPosition(_label->GetText()->GetLength());
}

};