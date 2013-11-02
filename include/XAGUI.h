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
	CONTROL_STATE_ACTIVE,
	CONTROL_STATE_DISABLED,
	CONTROL_STATE_COUNT,
};

enum Orientation
{
	ORIENTATION_HORIZONTAL,
	ORIENTATION_VERTICAL,
	ORIENTATION_COUNT
};

#define TouchMoveEvent MouseMoveEvent
#define TouchEvent(x,y,down) MouseButtonEvent(x,y,XAGUI::MOUSE_BUTTON_LEFT,down)

typedef fastdelegate::FastDelegate0<void> TextInput;

#include "Font.h"
#include "Texture.h"
#include "StaticText.h"
#include "Renderer.h"
#include "Control.h"
#include "Label.h"
#include "Button.h"
#include "Slider.h"
#include "TextBox.h"
#include "PasswordTextBox.h"
#include "MultilineTextBox.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "PictureBox.h"
#include "ProggressBar.h"
#include "AnalogStick.h"
#include "Window.h"
#include "Form.h"

class XAGUI
{
	public:

		/**
		 * Starts text input.
		 * Mobile platforms should show virtual keyboard.
		 */
		static void StartTextInput();

		/**
		 * Stops text input.
		 * Mobile platforms should hide virtual keyboard.
		 */
		static void StopTextInput();

		/**
		 * Returns true if text input is started, false if not.
		 * @return Whether text input is started.
		 */
		static inline bool IsTextInputStarted() { return _textInputStarted; }

		/**
		 * Returns current used renderer for form rendering.
		 * @return Current used renderer.
		 */
		static inline Renderer* GetRenderer() { return _renderer; }

		/**
		 * Returns current used skin for form rendering.
		 * @return Current used skin.
		 */
		static inline Texture* GetSkin() { return _skin; }

		/**
		 * Sets pointer to renderer.
		 * @param renderer Pointer to renderer.
		 */
		static void SetRenderer(Renderer* renderer);

		/**
		 * Sets pointer to skin texture.
		 * @param skin Pointer to skin texture.
		 */
		static void SetSkin(Texture* skin);

		/**
		 * Sets function for start text input.
		 * @see StartTextInput()
		 * @param startTextInput Function to start text input.
		 */
		static void SetStartTextInput(TextInput startTextInput);

		/**
		 * Sets function for stop text input.
		 * @see StopTextInput()
		 * @param stopTextInput Function to stop text input.
		 */
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