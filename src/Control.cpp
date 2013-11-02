#include "XAGUI.h"

namespace XAGUI
{

OnControlCreation Control::onControlCreation;
Control* Control::_focusedControl = 0;

Control::Control()
	: _state(CONTROL_STATE_NORMAL), _x(0), _y(0), _width(0), _height(0), _center(false), _visible(true), 
	_consumeMouseEvents(false), _consumeKeyboardEvents(false), _parent(0)
{
	for (uchar i = 0; i < CONTROL_STATE_COUNT; i++)
		SetColor(static_cast<ControlState>(i), 255, 255, 255, 255);
}

Control::~Control()
{
	DeleteAllChildren();
}

void Control::ReadProperties(tinyxml2::XMLElement* element)
{
	std::string string;

	if (strcmp(element->Name(), "form") != 0)
		_type = element->Attribute("type");

	SetID(element->Attribute("id"));

	cchar* cstring = element->Attribute("w");
	if (cstring != 0)
	{
		string = cstring;
		if (string.compare("AUTO") == 0)
		{
			SetAutoWidth();
		}
		else if (*string.rbegin() == 'p')
		{
			SetPermilWidth(xaih::StrToUInt(xaih::ParseString(string, "p").c_str()));
		}
		else
		{
			SetWidth(xaih::StrToUInt(string.c_str()));
		}
	}
	else
	{
		SetWidth(0);
	}

	cstring = element->Attribute("h");
	if (cstring != 0)
	{
		string = cstring;
		if (string.compare("AUTO") == 0)
		{
			SetAutoHeight();
		}
		else if (*string.rbegin() == 'p')
		{
			SetPermilHeight(xaih::StrToUInt(xaih::ParseString(string, "p").c_str()));
		}
		else
		{
			SetHeight(xaih::StrToUInt(string.c_str()));
		}
	}
	else
	{
		SetHeight(0);
	}

	_center = element->BoolAttribute("center");

	string = element->Attribute("x");
	if (*string.rbegin() == 'p')
	{
		SetPermilX(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), _center);
	}
	else
	{
		SetX(xaih::StrToInt(string.c_str()));
	}

	string = element->Attribute("y");
	if (*string.rbegin() == 'p')
	{
		SetPermilY(xaih::StrToInt(xaih::ParseString(string, "p").c_str()), _center);
	}
	else
	{
		SetY(xaih::StrToInt(string.c_str()));
	}

	cstring = element->Attribute("color");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			SetColor(CONTROL_STATE_NORMAL, (color >> 24) & 0xff, (color >> 16) & 0xff, 
			(color >> 8) & 0xff, color & 0xff);
		}
	}
	
	cstring = element->Attribute("hColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			SetColor(CONTROL_STATE_HOVER, (color >> 24) & 0xff, (color >> 16) & 0xff, 
			(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("aColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			SetColor(CONTROL_STATE_ACTIVE, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("dColor");
	if (cstring != 0 && strlen(cstring) == 9 && cstring[0] == '#')
	{
		uint color;
		sscanf(cstring + 1, "%x", &color);
		if (color != 0)
		{
			SetColor(CONTROL_STATE_DISABLED, (color >> 24) & 0xff, (color >> 16) & 0xff, 
				(color >> 8) & 0xff, color & 0xff);
		}
	}

	cstring = element->Attribute("visible");
	if (cstring != 0)
		SetVisible(xaih::StrToBool(cstring));

	cstring = element->Attribute("consumeMouseEvents");
	if (cstring != 0)
		SetConsumeMouseEvents(xaih::StrToBool(cstring));

	cstring = element->Attribute("consumeKeyboardEvents");
	if (cstring != 0)
		SetConsumeKeyboardEvents(xaih::StrToBool(cstring));
}

void Control::ParseChildren(tinyxml2::XMLElement* element)
{
	if (!element->NoChildren())
	{
		Control* child;
		tinyxml2::XMLNode* node = element->FirstChild();
		while (node != 0)
		{
			child = 0;
			
			cchar* type = node->ToElement()->Attribute("type");
			if (strcmp(type, "Window") == 0)
			{
				child = new Window(node->ToElement(), this);
			}
			else if (strcmp(type, "Label") == 0)
			{
				child = new Label(node->ToElement(), this);
			}
			else if (strcmp(type, "PictureBox") == 0)
			{
				child = new PictureBox(node->ToElement(), this);
			}
			else if (strcmp(type, "Button") == 0)
			{
				child = new Button(node->ToElement(), this);
			}
			else if (strcmp(type, "CheckBox") == 0)
			{
				child = new CheckBox(node->ToElement(), this);
			}
			else if (strcmp(type, "RadioButton") == 0)
			{
				child = new RadioButton(node->ToElement(), this);
			}
			else if (strcmp(type, "TextBox") == 0)
			{
				child = new TextBox(node->ToElement(), this);
			}
			else if (strcmp(type, "PasswordTextBox") == 0)
			{
				child = new PasswordTextBox(node->ToElement(), this);
			}
			else if (strcmp(type, "MultilineTextBox") == 0)
			{
				child = new MultilineTextBox(node->ToElement(), this);
			}
			else if (strcmp(type, "Slider") == 0)
			{
				child = new Slider(node->ToElement(), this);
			}
			else if (strcmp(type, "ProggressBar") == 0)
			{
				child = new ProggressBar(node->ToElement(), this);
			}
			else if (strcmp(type, "AnalogStick") == 0)
			{
				child = new AnalogStick(node->ToElement(), this);
			}
			
			if (onControlCreation != 0)
				onControlCreation(type, child);

			if (child != 0)
			{
				AddChild(child);
				child->ParseChildren(node->ToElement());
			}

			node = node->NextSibling();
		}
	}
}

void Control::AddChild(Control* control)
{
	control->SetParent(this);
	_children.push_back(control);
}

void Control::RemoveAllChildren()
{
	_children.clear();
}

void Control::DeleteAllChildren()
{
	for (uint i = 0; i < _children.size(); i++)
	{
		if (_children[i] == GetFocusedControl())
			SetFocusedControl(0);

		SAFE_DELETE(_children[i]);
	}
	_children.clear();
}

void Control::Render()
{
	for (uint i = 0; i < _children.size(); i++)
		_children[i]->Render();
}

sint Control::GetAbsX() const
{
	if (GetParent() != 0)
		return GetParent()->GetAbsX() + GetX();
	
	return GetX();
}

sint Control::GetAbsY() const
{
	if (GetParent() != 0) return (GetParent()->GetAbsY() + GetY());
	return GetX();
}

Control* Control::GetChild(cchar* id) const
{
	Control* child;
	for (uint i = 0; i < _children.size(); i++)
	{
		if (strcmp(_children[i]->GetID(), id) == 0)
		{
			return _children[i];
		}
		else
		{
			child = _children[i]->GetChild(id);
			if (child != 0) return child;
		}
	}
	return 0;
}

void Control::SetState(ControlState state)
{
	_state = state;

	if (onControlStateChanged != 0)
	{
		onControlStateChanged(this, state);
	}
	else
	{
		OnControlStateChangedEvent(state);
	}
}

void Control::SetX(sint x)
{
	_x = x;

	if (IsCentered())
	{
		_x = x - static_cast<sint>(GetWidth() / 2.0f);
	}
}

void Control::SetPermilX(sint permil, bool center)
{
	if (GetParent() == 0)
	{
		SetX(static_cast<sint>(XAGUI::GetRenderer()->GetBackBufferWidth() * (permil / 1000.0f)));
	}
	else
	{
		SetX(static_cast<sint>(_parent->GetWidth() * (permil / 1000.0f)));
	}
}

void Control::SetY(sint y)
{
	_y = y;

	if (IsCentered())
		_y = y - static_cast<sint>(GetHeight() / 2.0f);
}

void Control::SetPermilY(sint permil, bool center)
{
	if (GetParent() == 0)
	{
		SetY(static_cast<sint>(XAGUI::GetRenderer()->GetBackBufferHeight() * (permil / 1000.0f)));
	}
	else
	{
		SetY(static_cast<sint>(_parent->GetHeight() * (permil / 1000.0f)));
	}
}

void Control::SetWidth(usint width)
{
	usint tempWidth = GetWidth();
	_width = width;
	if (IsCentered())
	{
		SetX(GetX() + static_cast<sint>(tempWidth / 2.0f));
	}
	else
	{
		SetX(GetX());
	}
}

void Control::SetPermilWidth(usint permil)
{
	SetWidth(static_cast<usint>(XAGUI::GetRenderer()->GetBackBufferWidth() * (permil / 1000.0f)));
}

void Control::SetAutoWidth()
{
	if (GetParent() == 0)
	{
		SetWidth(XAGUI::GetRenderer()->GetBackBufferWidth());
	}
	else
	{
		SetWidth(_parent->GetWidth());
	}
}

void Control::SetHeight(usint height)
{
	usint tempHeight = GetHeight();
	_height = height;
	if (IsCentered())
	{
		SetY(GetY() + static_cast<sint>(tempHeight / 2.0f));
	}
	else
	{
		SetY(GetY());
	}
}

void Control::SetPermilHeight(usint permil)
{
	SetHeight(static_cast<usint>(XAGUI::GetRenderer()->GetBackBufferHeight() * (permil / 1000.0f)));
}

void Control::SetAutoHeight()
{
	if (GetParent() == 0)
	{
		SetHeight(XAGUI::GetRenderer()->GetBackBufferHeight());
	}
	else
	{
		SetHeight(_parent->GetHeight());
	}
}

void Control::SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha)
{
	_red[controlState] = red;
	_green[controlState] = green;
	_blue[controlState] = blue;
	_alpha[controlState] = alpha;
}

void Control::SetFocusedControl(Control* control)
{
	if (control != GetFocusedControl())
	{
		if (GetFocusedControl() != 0)
		{
			if (GetFocusedControl()->onLostFocus != 0)
			{
				GetFocusedControl()->onLostFocus(GetFocusedControl());
			}
			else
			{
				GetFocusedControl()->OnLostFocus();
			}
		}
	
		_focusedControl = control;

		if (control != 0)
			(control->onGetFocus != 0) ? control->onGetFocus(control) : control->OnGetFocus();
	}
}

void Control::MouseMoveEvent(int x, int y)
{
	(onMouseMove != 0) ? onMouseMove(this, x, y) : OnMouseMoveEvent(x, y);
}

bool Control::MouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	if (onMouseButton != 0) 
	{
		onMouseButton(this, x, y, button, down);
	}
	else
	{
		OnMouseButtonEvent(x, y, button, down);
	}

	return IsConsumeMouseEvents();
}

bool Control::MouseEvent(int x, int y, MouseButton button, bool down)
{
	if (IsVisible() && !IsDisabled())
	{
		for (uint i = 0; i < _children.size(); i++)
		{
			if (_children[i]->MouseEvent(x, y, button, down)) return true;
		}

		if (xaih::IsPointInRectangle(static_cast<float>(x), static_cast<float>(y), 
			static_cast<float>(GetAbsX()), static_cast<float>(GetAbsY()), GetWidth(), GetHeight()))
		{
			if (GetState() == CONTROL_STATE_NORMAL)
			{
				SetState(CONTROL_STATE_HOVER);
			}
			else if (GetState() == CONTROL_STATE_HOVER && button == MOUSE_BUTTON_LEFT && down)
			{
				SetState(CONTROL_STATE_ACTIVE);
				SetFocusedControl(this);
				return true;
			}
			else if (GetState() == CONTROL_STATE_ACTIVE)
			{
				if (button == MOUSE_BUTTON_LEFT && !down)
				{
					SetState(CONTROL_STATE_HOVER);
					(onClick != 0) ? onClick(this) : OnClickEvent();
				}
				return true;
			}
		}
		else
		{
			SetState(CONTROL_STATE_NORMAL);
		}
	}
	
	return false;
}

bool Control::KeyEvent(Key key, bool down)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
		return GetFocusedControl()->KeyEvent(key, down);

	return Control::IsConsumeKeyboardEvents();
}

bool Control::TextInputEvent(std::string text)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
		return GetFocusedControl()->TextInputEvent(text);

	return Control::IsConsumeKeyboardEvents();
}

void Control::OnMouseMoveEvent(int x, int y)
{
	for (uint i = 0; i < _children.size(); i++)
		_children[i]->MouseMoveEvent(x, y);
}

void Control::OnMouseButtonEvent(int x, int y, MouseButton button, bool down)
{
	for (uint i = 0; i < _children.size(); i++)
		_children[i]->MouseButtonEvent(x, y, button, down);
}

void Control::OnKeyEvent(Key key, bool down)
{

}

void Control::OnTextInputEvent(std::string text)
{

}

void Control::OnControlStateChangedEvent(ControlState state)
{

}

void Control::OnGetFocus()
{

}

void Control::OnLostFocus()
{

}

void Control::OnClickEvent()
{

}

};