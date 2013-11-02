#ifndef XAGUI_RADIO_BUTTON_H
#define XAGUI_RADIO_BUTTON_H

class RadioButton : public CheckBox
{
	public:

		/**
		 * Constructor
		 */
		RadioButton();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		RadioButton(tinyxml2::XMLElement* element, Control* parent);

		/**
		 * Destructor
		 */
		virtual ~RadioButton();

	public:

		/**
		 * Called when control is clicked.
		 */
		virtual void OnClickEvent();
};

#endif