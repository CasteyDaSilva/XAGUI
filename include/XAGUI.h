#ifndef XANDEV_AWESOME_GUI_H
#define XANDEV_AWESOME_GUI_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "xaih/xaih.h"
#include "FastDelegate/FastDelegate.h"
#include "XML/tinyxml2.h"

namespace XAGUI
{

enum ControlState
{
	CONTROL_STATE_NORMAL,
	CONTROL_STATE_HOVER,
	CONTROL_STATE_ACTIVE,
	CONTROL_STATE_DISABLED,
	CONTROL_STATE_COUNT,
};

enum Alignment
{
    ALIGNMENT_LEFT = 0x01,
    ALIGNMENT_HCENTER = 0x02,
    ALIGNMENT_RIGHT = 0x04,
    ALIGNMENT_TOP = 0x10,
    ALIGNMENT_VCENTER = 0x20,
    ALIGNMENT_BOTTOM = 0x40,
    ALIGNMENT_TOP_LEFT = ALIGNMENT_TOP | ALIGNMENT_LEFT,
    ALIGNMENT_VCENTER_LEFT = ALIGNMENT_VCENTER | ALIGNMENT_LEFT,
    ALIGNMENT_BOTTOM_LEFT = ALIGNMENT_BOTTOM | ALIGNMENT_LEFT,
    ALIGNMENT_TOP_HCENTER = ALIGNMENT_TOP | ALIGNMENT_HCENTER,
    ALIGNMENT_VCENTER_HCENTER = ALIGNMENT_VCENTER | ALIGNMENT_HCENTER,
    ALIGNMENT_BOTTOM_HCENTER = ALIGNMENT_BOTTOM | ALIGNMENT_HCENTER,
    ALIGNMENT_TOP_RIGHT = ALIGNMENT_TOP | ALIGNMENT_RIGHT,
    ALIGNMENT_VCENTER_RIGHT = ALIGNMENT_VCENTER | ALIGNMENT_RIGHT,
    ALIGNMENT_BOTTOM_RIGHT = ALIGNMENT_BOTTOM | ALIGNMENT_RIGHT,
	ALIGMENT_COUNT
};

enum Orientation
{
	ORIENTATION_HORIZONTAL,
	ORIENTATION_VERTICAL,
	ORIENTATION_COUNT
};

#define TouchMoveEvent MouseMoveEvent
#define TouchDownEvent(x,y) MouseButtonDownEvent(x,y,SDL_BUTTON_LEFT)
#define TouchUpEvent(x,y) MouseButtonUpEvent(x,y,SDL_BUTTON_LEFT)

#include "Font.h"
#include "Texture.h"
#include "StaticText.h"
#include "Renderer.h"

#include "ControlBase.h"
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
		 * Mobile platforms should show on-screen keyboard.
		 */
		static void StartTextInput();

		/**
		 * Stops text input.
		 * Mobile platforms should hide on-screen keyboard.
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

	private:

		static Renderer* _renderer;
		static Texture* _skin;
		static bool _textInputStarted;
};

};

#endif