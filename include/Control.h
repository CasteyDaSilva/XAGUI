#ifndef XAGUI_CONTROL_H
#define XAGUI_CONTROL_H

class Control;

typedef fastdelegate::FastDelegate2<cchar*, Control*, void> OnControlCreation;
typedef fastdelegate::FastDelegate3<Control*, int, int, void> OnMouseMove;
typedef fastdelegate::FastDelegate4<Control*, int, int, uchar, void> OnMouseButtonDown;
typedef fastdelegate::FastDelegate4<Control*, int, int, uchar, void> OnMouseButtonUp;
typedef fastdelegate::FastDelegate2<Control*, SDL_Scancode, void> OnKeyDown;
typedef fastdelegate::FastDelegate2<Control*, SDL_Scancode, void> OnKeyUp;
typedef fastdelegate::FastDelegate2<Control*, std::string, void> OnTextInput;
typedef fastdelegate::FastDelegate1<Control*, void> OnControlStateChanged;
typedef fastdelegate::FastDelegate1<Control*, void> OnFocus;
typedef fastdelegate::FastDelegate1<Control*, void> OnClick;
typedef fastdelegate::FastDelegate1<Control*, void> OnValueChanged;

class Control : public ControlBase
{
	public:

		/**
		 * Constructor
		 */
		Control();

		/**
		 * Destructor
		 */
		virtual ~Control();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);

		/**
		 * Parses children from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ParseChildren(tinyxml2::XMLElement* element);
		
		/**
		 * Adds control as child.
		 * @param control Control to be added as child.
		 */
		virtual void AddChild(Control* control);
		
		/**
		 * Removes all children from children list.
		 */
		virtual void RemoveAllChildren();

		/**
		 * Deletes(operator) and removes all children from children list.
		 */
		virtual void DeleteAllChildren();

		/**
		 * Renders all children control.
		 */
		virtual void Render();

		/**
		 * Shows control.
		 */
		virtual inline void Show() { SetVisible(true); }

		/**
		 * Hides control.
		 */
		virtual inline void Hide() { SetVisible(false); }

		/**
		 * Moves specified child control to front.
		 * @param control Control to be moved to front.
		 */
		virtual void MoveChildToFront(Control* control);
		
		/**
		 * Moves control to front.
		 */
		virtual void MoveToFront();

		/**
		 * Returns true if control is hovered, false if not.
		 * @return Whether control is hovered.
		 */
		virtual inline bool IsHovered() const 
		{ return (GetState() == CONTROL_STATE_HOVER) ? true : false; }

		/**
		 * Returns true if control is active, false if not.
		 * @return Whether control is active.
		 */
		virtual inline bool IsActive() const
		{ return (GetState() == CONTROL_STATE_ACTIVE) ? true : false; }

		/**
		 * Returns true if control is disabled, false if not.
		 * @return Whether control is disabled.
		 */
		virtual inline bool IsDisabled() const
		{ return (GetState() == CONTROL_STATE_DISABLED) ? true : false; }
		
		/**
		 * Returns true if control is visible, false if not.
		 * @return Whether control is visible.
		 */
		virtual inline bool IsVisible() const { return _visible; }

		/**
		 * Returns true if control is consuming mouse events, false if not.
		 * @return Whether control is consuming mouse events.
		 */
		virtual inline bool IsConsumeMouseEvents() const { return _consumeMouseEvents; }

		/**
		 * Returns true if control is consuming keyboard events, false if not.
		 * @return Whether control is consuming keyboard events.
		 */
		virtual inline bool IsConsumeKeyboardEvents() const { return _consumeKeyboardEvents; }
		
		/**
		 * Returns true if control is focused, false if not.
		 * @return Whether control is focused.
		 */
		virtual inline bool IsFocused() const { return (Control::GetFocusedControl() == this); }

		virtual inline sint GetX() const { return _x; }

		virtual inline sint GetY() const { return _y; }

		virtual sint GetAlignmentX() const;
		
		virtual sint GetAlignmentY() const;

		virtual sint GetAbsX() const;

		virtual sint GetAbsY() const;

		virtual inline usint GetWidth() const { return _width; }

		virtual inline usint GetHeight() const { return _height; }

		virtual inline Alignment GetAlignment() const { return _alignment; }

		/**
		 * Returns control state.
		 * @return Control state.
		 */
		virtual inline ControlState GetState() const { return _state; }

		virtual inline SDL_Color GetColor(ControlState controlState) const 
		{ return _color[controlState]; }

		/**
		 * Returns control's parent.
		 * @return Control's parent.
		 */
		virtual inline Control* GetParent() const { return _parent; }

		virtual Control* GetChild(cchar* id) const;
		
		virtual Control* GetChild(uint i) const { return _children[i]; }

		virtual uint GetChildrenCount() const { return _children.size(); }

		static inline Control* GetFocusedControl() { return _focusedControl; }

		virtual inline void SetX(sint x) { _x = x; }

		virtual void SetRatioX(double ratio);

		virtual inline void SetY(sint y) { _y = y; }

		virtual void SetRatioY(double ratio);

		virtual void SetWidth(usint width);

		virtual void SetRatioWidth(double ratio);

		virtual void SetAutoWidth();
		
		virtual void SetHeight(usint height);

		virtual void SetRatioHeight(double ratio);

		virtual void SetAutoHeight();
		
		virtual void SetAlignment(Alignment alignment) { _alignment = alignment; }

		virtual void SetState(ControlState state);

		virtual void SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha);

		virtual void SetColor(ControlState controlState, SDL_Color color);

		virtual inline void SetVisible(bool visible) { _visible = visible; }

		virtual inline void SetConsumeMouseEvents(bool consumeMouseEvents) 
		{ _consumeMouseEvents = consumeMouseEvents; }

		virtual inline void SetConsumeKeyboardEvents(bool consumeKeyboardEvents) 
		{ _consumeKeyboardEvents = consumeKeyboardEvents; }
		
		virtual inline void SetParent(Control* parent) { _parent = parent; }

		static void SetFocusedControl(Control* control);

	public:

		virtual Control* MouseMoveEvent(int x, int y);

		/**
		 * 
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 */
		virtual Control* MouseButtonDownEvent(int x, int y, uchar button);
		
		/**
		 * 
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Released mouse button.
		 */
		virtual void MouseButtonUpEvent(int x, int y, uchar button);

		/**
		 * Sends this event to focused control.
		 * @param key Pressed key.
		 */
		virtual bool KeyDownEvent(SDL_Scancode key);
		
		/**
		 * Sends this event to focused control.
		 * @param key Released key.
		 */
		virtual bool KeyUpEvent(SDL_Scancode key);

		/**
		 * Sends this event to focused control.
		 * @param text Typed text.
		 */
		virtual bool TextInputEvent(std::string text);
		
		/**
		 * Called when mouse is moved.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed/Released mouse button.
		 * @param down Whether is pressed button.
		 */
		virtual void OnMouseMoveEvent(int x, int y);

		/**
		 * Called when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 */
		virtual void OnMouseButtonDownEvent(int x, int y, uchar button);
		
		/**
		 * Called when mouse button is released.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Released mouse button.
		 */
		virtual void OnMouseButtonUpEvent(int x, int y, uchar button);

		/**
		 * Called when key is pressed.
		 * @param key Pressed key.
		 */
		virtual void OnKeyDownEvent(SDL_Scancode key);
		
		/**
		 * Called when key is released.
		 * @param key Released key.
		 */
		virtual void OnKeyUpEvent(SDL_Scancode key);

		/**
		 * Called when text input mode is on.
		 * @param text Typed text.
		 */
		virtual void OnTextInputEvent(std::string text);
		
		/**
		 * Called when control state is changed.
		 * @param state New control state.
		 */
		virtual void OnControlStateChangedEvent();
		
		/**
		 * Called when control gets focus.
		 */
		virtual void OnGotFocusEvent();

		/**
		 * Called when control lost focus.
		 */
		virtual void OnLostFocusEvent();

		/**
		 * Called when control is clicked.
		 */
		virtual void OnClickEvent();

	public:

		static OnControlCreation onControlCreation;

		OnMouseMove onMouseMove;
		OnMouseButtonDown onMouseButtonDown;
		OnMouseButtonUp onMouseButtonUp;
		OnKeyDown onKeyDown;
		OnKeyUp onKeyUp;
		OnControlStateChanged onControlStateChanged;
		OnFocus onGotFocus;
		OnFocus onLostFocus;
		OnClick onClick;

	protected:

		sint _x;
		sint _y;
		usint _width;
		usint _height;
		Alignment _alignment;
		ControlState _state;
		SDL_Color _color[CONTROL_STATE_COUNT];
		bool _visible;
		bool _consumeMouseEvents;
		bool _consumeKeyboardEvents;

		Control* _parent;
		std::vector<Control*> _children;

		static Control* _focusedControl;
};

#endif