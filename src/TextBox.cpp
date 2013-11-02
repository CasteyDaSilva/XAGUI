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
		if (*string.rbegin() == 'p')
		{
			_label->SetPermilX(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), textCenter);
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
		if (*string.rbegin() == 'p')
		{
			_label->SetPermilY(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), textCenter);
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
				GetCaretSrcWidth(), GetCaretSrcHeight(), _label->GetRed(GetState()), 
				_label->GetGreen(GetState()), _label->GetBlue(GetState()), _label->GetAlpha(GetState()));
		}
	}
}

void TextBox::InsertText(cchar* text, int position)
{
	_label->GetStaticText()->GetPointerToString()->insert(GetCaretPosition(), text);
	SetText(_label->GetStaticText()->Get());
	SetCaretPosition(GetCaretPosition() + strlen(text));
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

bool TextBox::MouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	if (button == MOUSE_BUTTON_LEFT && down)
	{
		if (xaih::IsPointInRectangle(static_cast<float>(x), static_cast<float>(y), 
			static_cast<float>(GetAbsX()), static_cast<float>(GetAbsY()), GetWidth(), GetHeight()))
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

	return Control::IsConsumeMouseEvents();
}

bool TextBox::KeyEvent(Key key, bool down)
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

	return Control::IsConsumeKeyboardEvents();
}

bool TextBox::TextInputEvent(std::string text)
{
	InsertText(text.c_str(), GetCaretPosition());
	return Control::IsConsumeKeyboardEvents();
}

};