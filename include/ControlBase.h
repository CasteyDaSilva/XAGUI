#ifndef XAGUI_CONTROL_BASE_H
#define XAGUI_CONTROL_BASE_H

class ControlBase
{
	public:

		/**
		 * Constructor
		 */
		ControlBase();

		/**
		 * Destructor
		 */
		virtual ~ControlBase();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);

		/**
		 * Returns control's id.
		 * @return Control's id.
		 */
		virtual inline cchar* GetID() const { return _id.c_str(); }

		/**
		 * Returns control's type.
		 * @return Control's type.
		 */
		virtual inline cchar* GetType() const { return _type.c_str(); }

		/**
		 * Sets id of control.
		 * @param id New id of control.
		 */
		virtual inline void SetID(cchar* id) { _id = id; }

	protected:

		std::string _id;
		std::string _type;
};

#endif