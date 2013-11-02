#ifndef XAGUI_SLIDER_H
#define XAGUI_SLIDER_H

typedef fastdelegate::FastDelegate2<Control*, int, void> OnValueChanged;

class Slider : public Button
{
	public:

		/**
		 * Constructor
		 */
		Slider();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		Slider(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~Slider();

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
		 * Returns control's orientation.
		 * @return Orientation of control.
		 */
		virtual inline Orientation GetOrientation() const { return _orientation; }

		/**
		 * Returns marker as button.
		 * @return Marker as button.
		 */
		virtual inline Button* GetMarker() const { return _marker; }
		
		/**
		 * Returns marker X offset.
		 * @return X offset of marker.
		 */
		virtual inline sint GetMarkerOffsetX() const { return _markerOffsetX; }
		
		/**
		 * Returns marker Y offset.
		 * @return Y offset of marker.
		 */
		virtual inline sint GetMarkerOffsetY() const { return _markerOffsetY; }
		
		/**
		 * Returns minimal value.
		 * @return Minimal value.
		 */
		virtual inline int GetMinValue() const { return _minValue; }
		
		/**
		 * Returns maximal value.
		 * @return Maximal value.
		 */
		virtual inline int GetMaxValue() const { return _maxValue; }

		/**
		 * Returns current value.
		 * @return Current value.
		 */
		virtual inline int GetValue() const { return _value; }
		
		/**
		 * Sets control's orientation.
		 * @param orientation New orientation of control.
		 */
		virtual inline void SetOrientation(Orientation orientation) { _orientation = orientation; }
		
		/**
		 * Sets X offset of marker.
		 * @param markerOffsetX New X offset of marker.
		 */
		virtual void SetMarkerOffsetX(sint markerOffsetX);
		
		/**
		 * Sets Y offset of marker.
		 * @param markerOffsetX New Y offset of marker.
		 */
		virtual void SetMarkerOffsetY(sint markerOffsetY);
		
		/**
		 * Sets minimal value.
		 * @param minValue New minimal value.
		 */
		virtual inline void SetMinValue(int minValue);

		/**
		 * Sets maximal value.
		 * @param maxValue New maximal value.
		 */
		virtual inline void SetMaxValue(int maxValue);

		/**
		 * Sets current value.
		 * @param value New current value.
		 */
		virtual void SetValue(int value);

	public:

		/**
		 * Moves marker to mouse position when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 */
		virtual void MouseMoveEvent(int x, int y);

		/**
		 * Moves marker to mouse position when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 * @param down Whether is pressed button.
		 */
		virtual bool MouseButtonEvent(int x, int y, MouseButton button, bool down);

	public:

		OnValueChanged onValueChanged;

	protected:

		Orientation _orientation;

		Button* _marker;
		sint _markerOffsetX;
		sint _markerOffsetY;

		int _value;
		int _minValue;
		int _maxValue;

		bool _pressed;
};

#endif
