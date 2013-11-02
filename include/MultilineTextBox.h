#ifndef XAGUI_MULTILINE_TEXT_BOX_H
#define XAGUI_MULTILINE_TEXT_BOX_H

class MultilineTextBox : public TextBox
{
	public:

		/**
		 * Constructor
		 */
		MultilineTextBox();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		MultilineTextBox(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~MultilineTextBox();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);
};

#endif