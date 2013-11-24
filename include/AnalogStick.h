#ifndef XAGUI_ANALOG_STICK_H
#define XAGUI_ANALOG_STICK_H

class AnalogStick : public Button
{
	public:

		/**
		 * Constructor
		 */
		AnalogStick();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		AnalogStick(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~AnalogStick();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);

		/**
		 * Renders control.
		 */
		virtual void Render();

		/**
		 * Resets position of analog stick to initial position.
		 */
		void ResetStick();

		/**
		 * Returns absolute X position of stick.
		 * @return Absolute X position of stick.
		 */
		virtual inline sint GetStickX() const { return _stickX; }

		/**
		 * Returns absolute Y position of stick.
		 * @return Absolute Y position of stick.
		 */
		virtual inline sint GetStickY() const { return _stickY; }

		/**
		 * Returns X position of texture region of stick.
		 * @param controlState State of control for returning.
		 * @return X position of texture region.
		 */
		virtual inline usint GetStickSrcX(ControlState controlState) const 
		{ return _stickSrcX[controlState]; }
		
		/**
		 * Returns Y position of texture region of stick.
		 * @param controlState State of control for returning.
		 * @return Y position of texture region.
		 */
		virtual inline usint GetStickSrcY(ControlState controlState) const 
		{ return _stickSrcY[controlState]; }

		/**
		 * Returns X value of stick.
		 * @return X value of stick.
		 */
		virtual inline float GetValueX() const { return _valueX; }
		
		/**
		 * Returns Y value of stick.
		 * @return Y value of stick.
		 */
		virtual inline float GetValueY() const { return _valueY; }
		
		/**
		 * Sets absolute X position of stick.
		 * @param stickX New absolute X position of stick.
		 */
		virtual void SetStickX(sint stickX);
		
		/**
		 * Sets absolute Y position of stick.
		 * @param stickX New absolute Y position of stick.
		 */
		virtual void SetStickY(sint stickY);
		
		/**
		 * Sets X value of stick.
		 * @param valueX New X value of stick.
		 */
		virtual void SetValueX(float valueX);

		/**
		 * Sets Y value of stick.
		 * @param valueY New Y value of stick.
		 */
		virtual void SetValueY(float valueY);

		/**
		 * Sets X position of texture region of stick.
		 * @param controlState State of control for changing.
		 * @param srcX New X position of texture region.
		 */
		virtual inline void SetStickSrcX(ControlState controlState, usint stickSrcX) 
		{ _stickSrcX[controlState] = stickSrcX; }
		
		/**
		 * Sets Y position of texture region of stick.
		 * @param controlState State of control for changing.
		 * @param srcX New Y position of texture region.
		 */
		virtual inline void SetStickSrcY(ControlState controlState, usint stickSrcY) 
		{ _stickSrcY[controlState] = stickSrcY; }
	
	public:

		/**
		 * Moves analog stick to mouse position when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 */
		virtual Control* MouseMoveEvent(int x, int y);

		/**
		 * Moves analog stick to mouse position when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 */
		virtual Control* MouseButtonDownEvent(int x, int y, uchar button);
	
		/**
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Released mouse button.
		 */
		virtual void MouseButtonUpEvent(int x, int y, uchar button);

		/**
		 * Called when control sets value.
		 * @param value New value
		 */
		virtual void OnValueChangedEvent();

	public:

		OnValueChanged onValueChanged;

	protected:

		sint _stickX;
		sint _stickY;
		usint _stickSrcX[CONTROL_STATE_COUNT];
		usint _stickSrcY[CONTROL_STATE_COUNT];

		float _valueX;
		float _valueY;

		bool _pressed;
};

#endif