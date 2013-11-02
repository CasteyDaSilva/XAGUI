#ifndef XAGUI_PROGGRESS_BAR_H
#define XAGUI_PROGGRESS_BAR_H

class ProggressBar : public Button
{
	public:

		/**
		 * Constructor
		 */
		ProggressBar();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		ProggressBar(tinyxml2::XMLElement* element, Control* parent);

		/**
		 * Destructor
		 */
		virtual ~ProggressBar();

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
		 * Returns current proggress.
		 * @return Current proggress.
		 */ 
		virtual inline uchar GetProggress() const { return _proggress; }
		
		/**
		 * Sets current proggress.
		 * @param proggress New proggress(0-100).
		 */ 
		virtual inline void SetProggress(uchar proggress) { _proggress = proggress; }

	protected:

		uchar _proggress;
		usint _proggressWidth;
};

#endif