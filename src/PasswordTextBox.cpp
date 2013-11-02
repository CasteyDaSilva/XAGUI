#include "XAGUI.h"

namespace XAGUI
{

PasswordTextBox::PasswordTextBox()
{

}

PasswordTextBox::PasswordTextBox(tinyxml2::XMLElement* element, Control* parent)
	: TextBox(element, parent)
{
	ReadProperties(element);
}

PasswordTextBox::~PasswordTextBox()
{

}

void PasswordTextBox::ReadProperties(tinyxml2::XMLElement* element)
{
	cchar* cstring = element->Attribute("passwordChar");
	if (cstring != 0)
		SetPasswordChar(cstring);

	SetText(TextBox::GetText());
}

void PasswordTextBox::RemoveCharacter(int position)
{
	if (GetCaretPosition() > 0 && _label->GetStaticText()->GetLength() > 0)
	{
		_label->GetStaticText()->GetPointerToString()->erase(position, 1);
		_text.erase(position, 1);
		_label->SetText(_label->GetStaticText()->Get());
		SetCaretPosition(position);
	}
}

void PasswordTextBox::SetText(cchar* text) 
{ 
	_text = text;

	std::string buffer;
	for (uint i = 0; i < strlen(text); i++)
		buffer += GetPasswordChar();

	TextBox::SetText(buffer.c_str()); 
}

bool PasswordTextBox::TextInputEvent(std::string text)
{
	_text += text;

	std::string buffer;
	for (uint i = 0; i < text.length(); i++)
		buffer += GetPasswordChar();

	_label->GetStaticText()->GetPointerToString()->insert(GetCaretPosition(), buffer.c_str());
	_label->SetText(_label->GetStaticText()->Get());
	SetCaretPosition(GetCaretPosition() + text.length());

	return Control::IsConsumeKeyboardEvents();
}

};