#ifndef XAGUI_CONTROL_H
#define XAGUI_CONTROL_H

class Control;

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

		Control();

		virtual ~Control();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void ParseChildren(tinyxml2::XMLElement* element);

		virtual void AddChild(Control* control);
		
		virtual void RemoveAllChildren();

		virtual void DeleteAllChildren();

		virtual bool IsHovered() const;

		virtual bool IsPressed() const;

		virtual bool IsDisabled() const;

		virtual inline bool IsVisible() const { return _visible; }
	
		virtual inline bool IsCentered() const { return _center; }

		virtual inline ControlState GetState() const { return _state; }

		virtual inline Control* GetParent() const { return _parent; }

		virtual inline cchar* GetID() const { return _id.c_str(); }

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

		virtual void SetParent(Control* parent);

		virtual void SetID(cchar* id);

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

		virtual void SetColor(uchar red, uchar green, uchar blue, uchar alpha);

		virtual void SetColorHover(uchar redHover, uchar greenHover, uchar blueHover, uchar alphaHover);

		virtual void SetColorPressed(uchar redPressed, uchar greenPressed, uchar bluePressed, 
			uchar alphaPressed);

		virtual void SetColorDisabled(uchar redDisabled, uchar greenDisabled, uchar blueDisabled, 
			uchar alphaDisabled);

		virtual void SetVisible(bool visible);

		static void SetFocusedControl(Control* control);

	public:

		virtual void MouseMoveEvent(int x, int y);

		virtual void MouseButtonEvent(int x, int y, MouseButton button, bool down);

		virtual bool MouseEvent(int x, int y, MouseButton button, bool down);

		virtual void KeyEvent(Key key, bool down);

		virtual void TextInputEvent(std::string text);

		virtual void OnMouseMoveEvent(int x, int y);

		virtual void OnMouseButtonEvent(int x, int y, MouseButton button, bool down);
		
		virtual void OnKeyEvent(Key key, bool down);

		virtual void OnTextInputEvent(std::string text);

		virtual void OnControlStateChangedEvent(ControlState state);

		virtual void OnGetFocus();

		virtual void OnLostFocus();

		virtual void OnClickEvent();

	protected:

		virtual void Render();

	public:

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

		Control* _parent;
		std::vector<Control*> _children;

		static Control* _focusedControl;
};

#endif