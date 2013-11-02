#ifndef XAGUI_CHECK_BOX_H
#define XAGUI_CHECK_BOX_H

class CheckBox : public Button
{
	public:

		/**
		 * Constructor
		 */
		CheckBox();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		CheckBox(tinyxml2::XMLElement* element, Control* parent);

		/**
		 * Destructor
		 */
		virtual ~CheckBox();

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
		 * Returns true if check box is checked, false if not.
		 * @return Whether check box is checked.
		 */
		virtual inline bool IsChecked() const { return _checked; }

		/**
		 * Returns X position of texture region of checked control.
		 * @param controlState State of control for returning.
		 * @return X position of texture region.
		 */
		virtual inline usint GetCheckedSrcX(ControlState controlState) const 
		{ return _checkedSrcX[controlState]; }
		
		/**
		 * Returns Y position of texture region of checked control.
		 * @param controlState State of control for returning.
		 * @return Y position of texture region.
		 */
		virtual inline usint GetCheckedSrcY(ControlState controlState) const 
		{ return _checkedSrcY[controlState]; }
		
		/**
		 * Sets X position of texture region of checked control.
		 * @param controlState State of control for changing.
		 * @param srcX New X position of texture region.
		 */
		virtual void SetCheckedSrcX(ControlState controlState, usint checkedsrcX);

		/**
		 * Sets Y position of texture region of checked control.
		 * @param controlState State of control for changing.
		 * @param srcX New Y position of texture region.
		 */
		virtual void SetCheckedSrcY(ControlState controlState, usint checkedSrcY);

		/**
		 * 
		 * @param
		 */
		virtual inline void SetChecked(bool checked) { _checked = checked; }

	public:

		/**
		 * Called when control is clicked.
		 */
		virtual void OnClickEvent();

	protected:

		usint _checkedSrcX[CONTROL_STATE_COUNT];
		usint _checkedSrcY[CONTROL_STATE_COUNT];

		bool _checked;
};

#endif