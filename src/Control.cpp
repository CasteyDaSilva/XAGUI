#include "XAGUI.h"

namespace XAGUI
{

OnControlCreation Control::onControlCreation;
Control* Control::_focusedControl = 0;

Control::Control()
	: _x(0), _y(0), _width(0), _height(0), _alignment(ALIGNMENT_TOP_LEFT), _state(CONTROL_STATE_NORMAL),
	_visible(true), _consumeMouseEvents(false), _consumeKeyboardEvents(false), _parent(0)
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

	cchar* cstring = element->Attribute("w");
	if (cstring != 0)
	{
		string = cstring;
		if (string.compare("AUTO") == 0) 
		{ 
			SetAutoWidth(); 
		}
		else if (*string.rbegin() == 'r')
		{ 
			SetRatioWidth(xaih::StrToDouble(xaih::ParseString(string, "r").c_str())); 
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
		else if (*string.rbegin() == 'r')
		{
			SetRatioHeight(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
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

	cstring = element->Attribute("x");
	if (cstring != 0)
	{
		string = cstring;
		if (*string.rbegin() == 'r')
		{
			SetRatioX(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
		}
		else
		{
			SetX(xaih::StrToInt(string.c_str()));
		}
	}

	cstring = element->Attribute("y");
	if (cstring != 0)
	{
		string = cstring;
		if (*string.rbegin() == 'r')
		{
			SetRatioY(xaih::StrToDouble(xaih::ParseString(string, "r").c_str()));
		}
		else
		{
			SetY(xaih::StrToInt(string.c_str()));
		}
	}

	cstring = element->Attribute("align");
	if (cstring != 0)
	{
		if (strcmp(cstring, "LEFT") == 0)
		{
			SetAlignment(ALIGNMENT_LEFT);
		}
		else if (strcmp(cstring, "HCENTER") == 0)
		{
			SetAlignment(ALIGNMENT_HCENTER);
		}
		else if (strcmp(cstring, "TOP") == 0)
		{
			SetAlignment(ALIGNMENT_TOP);
		}
		else if (strcmp(cstring, "VCENTER") == 0)
		{
			SetAlignment(ALIGNMENT_VCENTER);
		}
		else if (strcmp(cstring, "BOTTOM") == 0)
		{
			SetAlignment(ALIGNMENT_BOTTOM);
		}
		else if (strcmp(cstring, "TOP_LEFT") == 0)
		{
			SetAlignment(ALIGNMENT_TOP_LEFT);
		}
		else if (strcmp(cstring, "VCENTER_LEFT") == 0)
		{
			SetAlignment(ALIGNMENT_VCENTER_LEFT);
		}
		else if (strcmp(cstring, "BOTTOM_LEFT") == 0)
		{
			SetAlignment(ALIGNMENT_BOTTOM_LEFT);
		}
		else if (strcmp(cstring, "TOP_HCENTER") == 0)
		{
			SetAlignment(ALIGNMENT_TOP_HCENTER);
		}
		else if (strcmp(cstring, "VCENTER_HCENTER") == 0)
		{
			SetAlignment(ALIGNMENT_VCENTER_HCENTER);
		}
		else if (strcmp(cstring, "BOTTOM_HCENTER") == 0)
		{
			SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		}
		else if (strcmp(cstring, "TOP_RIGHT") == 0)
		{
			SetAlignment(ALIGNMENT_TOP_RIGHT);
		}
		else if (strcmp(cstring, "VCENTER_RIGHT") == 0)
		{
			SetAlignment(ALIGNMENT_VCENTER_RIGHT);
		}
		else if (strcmp(cstring, "BOTTOM_RIGHT") == 0)
		{
			SetAlignment(ALIGNMENT_BOTTOM_RIGHT);
		}
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

	ControlBase::ReadProperties(element);
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
	for (uint i = 0; i < GetChildrenCount(); i++)
	{
		if (GetChild(i) == GetFocusedControl())
			SetFocusedControl(0);

		SAFE_DELETE(_children[i]);
	}

	RemoveAllChildren();
}

void Control::Render()
{
	for (uint i = 0; i < GetChildrenCount(); i++)
		GetChild(i)->Render();
}

void Control::MoveChildToFront(Control* control)
{
	for (uint i = 0; i < GetChildrenCount(); i++)
	{
		if (GetChild(i) == control)
		{
			uint dst = GetChildrenCount();
			const size_t finalDst = dst > i ? dst - 1 : dst;

			std::vector<Control*> tmp(_children.begin() + i, _children.begin() + i + 1);
			_children.erase(_children.begin() + i, _children.begin() + i + 1);
			_children.insert(_children.begin() + finalDst, tmp.begin(), tmp.end());

			break;
		}
	}
}

void Control::MoveToFront()
{
	Control* child = this;
	Control* parent = GetParent();

	while (parent != 0)
	{
		parent->MoveChildToFront(child);
		
		child = parent;
		parent = parent->GetParent();
	}
}

sint Control::GetAlignmentX() const
{
	if (GetAlignment() & ALIGNMENT_HCENTER)
	{
		if (GetParent() != 0) 
		{
			return static_cast<sint>((GetParent()->GetWidth() - GetWidth()) / 2.0f);
		}
		else
		{
			return static_cast<sint>((XAGUI::GetRenderer()->GetBackBufferWidth() - GetWidth()) / 2.0f);
		}
	}
	else if (GetAlignment() & ALIGNMENT_RIGHT) 
	{
		if (GetParent() != 0) 
		{
			return GetParent()->GetWidth() - GetWidth();
		}
		else
		{
			return XAGUI::GetRenderer()->GetBackBufferWidth() - GetWidth();
		}
	}

	// ALIGNMENT_LEFT
	return 0;
}

sint Control::GetAlignmentY() const
{
	if (GetAlignment() & ALIGNMENT_VCENTER)
	{
		if (GetParent() != 0) 
		{
			return static_cast<sint>((GetParent()->GetHeight() - GetHeight()) / 2.0f);
		}
		else
		{
			return static_cast<sint>((XAGUI::GetRenderer()->GetBackBufferHeight() - GetHeight()) / 2.0f);
		}
	}
	else if (GetAlignment() & ALIGNMENT_BOTTOM) 
	{
		if (GetParent() != 0) 
		{
			return GetParent()->GetHeight() - GetHeight();
		}
		else
		{
			return XAGUI::GetRenderer()->GetBackBufferHeight() - GetHeight();
		}
	}

	// ALIGNMENT_TOP
	return 0;
}

sint Control::GetAbsX() const
{
	if (GetParent() != 0) 
	{
		return GetParent()->GetAbsX() + GetAlignmentX() + GetX();
	}
	else 
	{
		return GetAlignmentX() + GetX();
	}
}

sint Control::GetAbsY() const
{
	if (GetParent() != 0) 
	{
		return GetParent()->GetAbsY() + GetAlignmentY() + GetY();
	}
	else 
	{
		return GetAlignmentY() + GetY();
	}
}

Control* Control::GetChild(cchar* id) const
{
	Control* child;
	for (uint i = 0; i < GetChildrenCount(); i++)
	{
		if (strcmp(GetChild(i)->GetID(), id) == 0)
		{
			return GetChild(i);
		}
		else
		{
			child = GetChild(i)->GetChild(id);
			if (child != 0) return child;
		}
	}
	return 0;
}

void Control::SetState(ControlState state)
{
	if (GetState() != state)
	{
		_state = state;

		if (onControlStateChanged != 0)
		{
			onControlStateChanged(this);
		}
		else
		{
			OnControlStateChangedEvent();
		}
	}
}

void Control::SetRatioX(double ratio)
{
	if (GetParent() == 0)
	{
		SetX(static_cast<sint>(xaih::Round(XAGUI::GetRenderer()->GetBackBufferWidth() * ratio)));
	}
	else
	{
		SetX(static_cast<sint>(xaih::Round(GetParent()->GetWidth() * ratio)));
	}
}

void Control::SetRatioY(double ratio)
{
	if (GetParent() == 0)
	{
		SetY(static_cast<sint>(xaih::Round(XAGUI::GetRenderer()->GetBackBufferHeight() * ratio)));
	}
	else
	{
		SetY(static_cast<sint>(xaih::Round(GetParent()->GetHeight() * ratio)));
	}
}

void Control::SetWidth(usint width)
{
	_width = width;
}

void Control::SetRatioWidth(double ratio)
{
	if (GetParent() == 0)
	{
		SetWidth(static_cast<usint>(xaih::Round(XAGUI::GetRenderer()->GetBackBufferWidth() * ratio)));
	}
	else
	{
		SetWidth(static_cast<usint>(xaih::Round(GetParent()->GetWidth() * ratio)));
	}
}

void Control::SetAutoWidth()
{
	if (GetParent() == 0)
	{
		SetWidth(XAGUI::GetRenderer()->GetBackBufferWidth());
	}
	else
	{
		SetWidth(GetParent()->GetWidth());
	}
}

void Control::SetHeight(usint height)
{
	_height = height;
}

void Control::SetRatioHeight(double ratio)
{
	if (GetParent() == 0)
	{
		SetHeight(static_cast<usint>(xaih::Round(XAGUI::GetRenderer()->GetBackBufferHeight() * ratio)));
	}
	else
	{
		SetHeight(static_cast<usint>(xaih::Round(GetParent()->GetHeight() * ratio)));
	}
}

void Control::SetAutoHeight()
{
	if (GetParent() == 0)
	{
		SetHeight(XAGUI::GetRenderer()->GetBackBufferHeight());
	}
	else
	{
		SetHeight(GetParent()->GetHeight());
	}
}

void Control::SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha)
{
	_color[controlState].r = red;
	_color[controlState].g = green;
	_color[controlState].b = blue;
	_color[controlState].a = alpha;
}

void Control::SetColor(ControlState controlState, SDL_Color color)
{
	SetColor(controlState, color.r, color.g, color.b, color.a);
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
				GetFocusedControl()->OnLostFocusEvent();
			}
		}
	
		_focusedControl = control;

		if (control != 0)
			(control->onGotFocus != 0) ? control->onGotFocus(control) : control->OnGotFocusEvent();
	}
}

Control* Control::MouseMoveEvent(int x, int y)
{
	if (IsVisible() && !IsDisabled())
	{
		Control* control = 0;

		// The last control on the list is the most on top.
		for (uint i = GetChildrenCount(); i > 0; i--)
		{
			// Search for child controls that consume this event.
			control = GetChild(i - 1)->MouseMoveEvent(x, y);

			// Check if we found it, if yes then return this child.
			//if (control != 0) return control;
		}

		if (GetState() == CONTROL_STATE_ACTIVE)
		{
			// Consumed by 'this' control!
			control = this;
		}
		else if (xaih::IsPointInRectangle(x, y, GetAbsX(), GetAbsY(), GetWidth(), GetHeight()))
		{
			if (GetState() == CONTROL_STATE_NORMAL)
			{
				SetState(CONTROL_STATE_HOVER);

				// Consumed by 'this' control!
				control = this;
			}
			else if (GetState() == CONTROL_STATE_HOVER)
			{
				// Consumed by 'this' control!
				control = this;
			}
		}
		else
		{
			SetState(CONTROL_STATE_NORMAL);
		}
		

		(onMouseMove != 0) ? onMouseMove(this, x, y) : OnMouseMoveEvent(x, y);	

		return control;
	}

	// Not consumed, due to invisible control or disabled.
	return 0;
}

Control* Control::MouseButtonDownEvent(int x, int y, uchar button)
{
	if (IsVisible() && !IsDisabled())
	{
		Control* control = 0;

		// The last control on the list is the most on top.
		for (uint i = GetChildrenCount(); i > 0; i--)
		{
			// Search for child controls that consume this event.
			control = GetChild(i - 1)->MouseButtonDownEvent(x, y, button);

			// Check if we found it, if yes then return this child.
			if (control != 0) return control;
		}

		if (GetState() == CONTROL_STATE_HOVER)
		{
			if (button == SDL_BUTTON_LEFT)
			{
				SetState(CONTROL_STATE_ACTIVE);
                SetFocusedControl(this);
				MoveToFront();

				// Consumed by 'this' control!
				control = this;
			}

			if (onMouseButtonDown != 0) 
			{
				onMouseButtonDown(this, x, y, button);
			}
			else
			{
				OnMouseButtonDownEvent(x, y, button);
			}

			return control;
		}
	}

	// Not consumed, due to invisible control or disabled.
	return 0;
}

void Control::MouseButtonUpEvent(int x, int y, uchar button)
{
	// The last control on the list is the most on top.
	for (uint i = GetChildrenCount(); i > 0; i--)
		GetChild(i - 1)->MouseButtonUpEvent(x, y, button);

	if (GetState() == CONTROL_STATE_ACTIVE && button == SDL_BUTTON_LEFT)
	{
		if (xaih::IsPointInRectangle(x, y, GetAbsX(), GetAbsY(), GetWidth(), GetHeight()))
		{
			SetState(CONTROL_STATE_HOVER);
			(onClick != 0) ? onClick(this) : OnClickEvent();
		}
		else
		{
			SetState(CONTROL_STATE_NORMAL);
		}
    }

	if (onMouseButtonUp != 0) 
	{
		onMouseButtonUp(this, x, y, button);
	}
	else
	{
		OnMouseButtonUpEvent(x, y, button);
	}
}

bool Control::KeyDownEvent(SDL_Scancode key)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
	{
		if (GetFocusedControl()->onKeyDown != 0)
		{
			GetFocusedControl()->onKeyDown(this, key);
		}
		else
		{
			GetFocusedControl()->OnKeyDownEvent(key);
		}

		return Control::IsConsumeKeyboardEvents();
	}
	return false;
}

bool Control::KeyUpEvent(SDL_Scancode key)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
	{
		if (GetFocusedControl()->onKeyUp != 0)
		{
			GetFocusedControl()->onKeyUp(this, key);
		}
		else
		{
			GetFocusedControl()->OnKeyUpEvent(key);
		}

		return Control::IsConsumeKeyboardEvents();
	}
	return false;
}

bool Control::TextInputEvent(std::string text)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
		return GetFocusedControl()->TextInputEvent(text);
	return false;
}

void Control::OnMouseMoveEvent(int x, int y)
{
	
}

void Control::OnMouseButtonDownEvent(int x, int y, uchar button)
{
	
}

void Control::OnMouseButtonUpEvent(int x, int y, uchar button)
{
	
}

void Control::OnKeyDownEvent(SDL_Scancode key)
{

}

void Control::OnKeyUpEvent(SDL_Scancode key)
{

}

void Control::OnTextInputEvent(std::string text)
{

}

void Control::OnControlStateChangedEvent()
{

}

void Control::OnGotFocusEvent()
{

}

void Control::OnLostFocusEvent()
{

}

void Control::OnClickEvent()
{

}


};