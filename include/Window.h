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

	protected:

};

#endif