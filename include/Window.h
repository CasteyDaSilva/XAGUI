#ifndef XAGUI_WINDOW_H
#define XAGUI_WINDOW_H

class Window : public Button
{
	public:

		/**
		 * Constructor
		 */
		Window();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		Window(tinyxml2::XMLElement* element, Control* parent);

		/**
		 * Destructor
		 */
		virtual ~Window();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);
		
		/**
		 * Renders control.
		 */
		virtual void Render();

		virtual inline bool IsDraggable() const { return _draggable; }

		virtual inline int GetDragX() const { return _dragX; }

		virtual inline int GetDragY() const { return _dragY; }

		virtual inline void SetDragX(int dragX) { _dragX = dragX; }

		virtual inline void SetDragY(int dragY) { _dragY = dragY; }

		virtual inline void SetDraggable(bool draggable) { _draggable = draggable; }

	public:

		/**
		 * mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 */
		virtual Control* MouseMoveEvent(int x, int y);

		/**
		 * mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 */
		virtual Control* MouseButtonDownEvent(int x, int y, uchar button);
		
	protected:

		int _dragX;
		int _dragY;

		bool _draggable;
};

#endif