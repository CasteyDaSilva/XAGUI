#ifndef XAGUI_CONTROL_H
#define XAGUI_CONTROL_H

class Control;

typedef fastdelegate::FastDelegate2<cchar*, Control*, void> OnControlCreation;
typedef fastdelegate::FastDelegate3<Control*, int, int, void> OnMouseMove;
typedef fastdelegate::FastDelegate5<Control*, int, int, MouseButton, bool, void> OnMouseButton;
typedef fastdelegate::FastDelegate3<Control*, Key, bool, void> OnKey;
typedef fastdelegate::FastDelegate2<Control*, std::string, void> OnTextInput;
typedef fastdelegate::FastDelegate2<Control*, ControlState, void> OnControlStateChanged;
typedef fastdelegate::FastDelegate1<Control*, void> OnFocus;
typedef fastdelegate::FastDelegate1<Control*, void> OnClick;

class Control
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
		 * Returns true if control is centered, false if not.
		 * @return Whether control is centered.
		 */
		virtual inline bool IsCentered() const { return _center; }
		
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

		/**
		 * Returns control state.
		 * @return Control state.
		 */
		virtual inline ControlState GetState() const { return _state; }

		/**
		 * Returns control's parent.
		 * @return Control's parent.
		 */
		virtual inline Control* GetParent() const { return _parent; }

		/**
		 * Returns control's id.
		 * @return Control's id.
		 */
		virtual inline cchar* GetID() const { return _id.c_str(); }

		/**
		 * Returns control's type.
		 * @return Control's type.
		 */
		virtual inline cchar* GetType() const { return _type.c_str(); }

		virtual inline sint GetX() const { return _x; }

		virtual inline sint GetY() const { return _y; }

		virtual sint GetAbsX() const;

		virtual sint GetAbsY() const;

		virtual inline usint GetWidth() const { return _width; }

		virtual inline usint GetHeight() const { return _height; }

		virtual inline uchar GetRed(ControlState controlState) const { return _red[controlState]; }

		virtual inline uchar GetGreen(ControlState controlState) const { return _green[controlState]; }

		virtual inline uchar GetBlue(ControlState controlState) const { return _blue[controlState]; }

		virtual inline uchar GetAlpha(ControlState controlState) const { return _alpha[controlState]; }

		virtual Control* GetChild(cchar* id) const;

		static inline Control* GetFocusedControl() { return _focusedControl; }

		virtual void SetState(ControlState state);

		virtual inline void SetParent(Control* parent) { _parent = parent; }

		virtual inline void SetID(cchar* id) { _id = id; }

		virtual void SetX(sint x);

		virtual void SetPermilX(sint permil, bool center = false);

		virtual void SetY(sint y);

		virtual void SetPermilY(sint permil, bool center = false);

		virtual void SetWidth(usint width);

		virtual void SetPermilWidth(usint permil);

		virtual void SetAutoWidth();
		
		virtual void SetHeight(usint height);

		virtual void SetPermilHeight(usint permil);

		virtual void SetAutoHeight();

		virtual void SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha);

		virtual inline void SetVisible(bool visible) { _visible = visible; }

		virtual inline void SetConsumeMouseEvents(bool consumeMouseEvents) 
		{ _consumeMouseEvents = consumeMouseEvents; }

		virtual inline void SetConsumeKeyboardEvents(bool consumeKeyboardEvents) 
		{ _consumeKeyboardEvents = consumeKeyboardEvents; }

		static void SetFocusedControl(Control* control);

	public:

		virtual void MouseMoveEvent(int x, int y);

		/**
		 * 
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed/Released mouse button.
		 * @param down Whether is pressed button.
		 */
		virtual bool MouseButtonEvent(int x, int y, MouseButton button, bool down);

		virtual bool MouseEvent(int x, int y, MouseButton button, bool down);
		
		/**
		 * Sends this event to focused control.
		 * @param key Pressed/Released key.
		 * @param down Whether is pressed key.
		 */
		virtual bool KeyEvent(Key key, bool down);

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
		 * Called when mouse button is pressed or released.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed/Released mouse button.
		 * @param down Whether is pressed button.
		 */
		virtual void OnMouseButtonEvent(int x, int y, MouseButton button, bool down);
		
		/**
		 * Called when key is pressed or released.
		 * @param key Pressed/Released key.
		 * @param down Whether is pressed key.
		 */
		virtual void OnKeyEvent(Key key, bool down);

		/**
		 * Called when text input mode is on.
		 * @param text Typed text.
		 */
		virtual void OnTextInputEvent(std::string text);
		
		/**
		 * Called when control state is changed.
		 * @param state New control state.
		 */
		virtual void OnControlStateChangedEvent(ControlState state);
		
		/**
		 * Called when control gets focus.
		 */
		virtual void OnGetFocus();

		/**
		 * Called when control lost focus.
		 */
		virtual void OnLostFocus();
		
		/**
		 * Called when control is clicked.
		 */
		virtual void OnClickEvent();

	public:

		static OnControlCreation onControlCreation;

		OnMouseMove onMouseMove;
		OnMouseButton onMouseButton;
		OnKey onKey;
		OnTextInput onTextInput;
		OnControlStateChanged onControlStateChanged;
		OnFocus onGetFocus;
		OnFocus onLostFocus;
		OnClick onClick;

	protected:

		ControlState _state;
		std::string _id;
		std::string _type;
		sint _x;
		sint _y;
		usint _width;
		usint _height;
		uchar _red[CONTROL_STATE_COUNT];
		uchar _green[CONTROL_STATE_COUNT];
		uchar _blue[CONTROL_STATE_COUNT]; 
		uchar _alpha[CONTROL_STATE_COUNT];
		bool _center;
		bool _visible;
		bool _consumeMouseEvents;
		bool _consumeKeyboardEvents;

		Control* _parent;
		std::vector<Control*> _children;

		static Control* _focusedControl;
};

#endif