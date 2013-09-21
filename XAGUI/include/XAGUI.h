#ifndef XANDEV_AWESOME_GUI_H
#define XANDEV_AWESOME_GUI_H

#include <vector>

#include "xaih/xaih.h"
#include "utf8/utf8.h"
#include "FastDelegate/FastDelegate.h"
#include "XML/tinyxml2.h"

namespace XAGUI
{

enum MouseButton
{
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_COUNT
};

enum Key
{
	KEY_LEFT_ARROW,
	KEY_RIGHT_ARROW,
	KEY_BACKSPACE,
	KEY_COUNT,
};

enum ControlState
{
	CONTROL_STATE_NORMAL,
	CONTROL_STATE_HOVER,
	CONTROL_STATE_PRESSED,
	CONTROL_STATE_DISABLED,
	CONTROL_STATE_COUNT,
};

#define TouchMoveEvent MouseMoveEvent
#define TouchEvent(x,y,down) MouseButtonEvent(x,y,XAGUI::MOUSE_BUTTON_LEFT,down)

typedef fastdelegate::FastDelegate0<void> TextInput;

#include "Font.h"
#include "Texture.h"
#include "Text.h"
#include "Renderer.h"
#include "Control.h"
#include "Label.h"
#include "Button.h"
#include "Slider.h"
#include "TextBox.h"
#include "CheckBox.h"
#include "StaticImage.h"
#include "ProggressBar.h"
#include "Window.h"
#include "Form.h"

class XAGUI
{
	public:

		static void StartTextInput();

		static void StopTextInput();

		static inline bool IsTextInputStarted() { return _textInputStarted; }

		static inline Renderer* GetRenderer() { return _renderer; }

		static inline Texture* GetSkin() { return _skin; }

		static void SetRenderer(Renderer* renderer);

		static void SetSkin(Texture* skin);

		static void SetStartTextInput(TextInput startTextInput);

		static void SetStopTextInput(TextInput stopTextInput);

	private:

		static Renderer* _renderer;
		static Texture* _skin;
		static TextInput _startTextInput;
		static TextInput _stopTextInput;
		static bool _textInputStarted;
};

};

#endif