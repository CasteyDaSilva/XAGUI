#ifndef XAGUI_BUTTON_H
#define XAGUI_BUTTON_H

class Button : public Control
{
	public:

		/**
		 * Constructor
		 */
		Button();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		Button(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~Button();

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
		 * Returns X position of texture region.
		 * @param controlState State of control for returning.
		 * @return X position of texture region.
		 */
		virtual inline usint GetSrcX(ControlState controlState) const { return _srcX[controlState]; }
		
		/**
		 * Returns Y position of texture region.
		 * @param controlState State of control for returning.
		 * @return Y position of texture region.
		 */
		virtual inline usint GetSrcY(ControlState controlState) const { return _srcY[controlState]; }
		
		/**
		 * Returns width of texture region.
		 * @return Width of texture region.
		 */
		virtual inline usint GetSrcWidth() const 
		{ return _srcWidth; }
		
		/**
		 * Returns height of texture region.
		 * @return Height of texture region.
		 */
		virtual inline usint GetSrcHeight() const 
		{ return _srcHeight; }

		/**
		 * Sets X position of texture region.
		 * @param controlState State of control for changing.
		 * @param srcX New X position of texture region.
		 */
		virtual void SetSrcX(ControlState controlState, usint srcX);
		
		/**
		 * Sets Y position of texture region.
		 * @param controlState State of control for changing.
		 * @param srcX New Y position of texture region.
		 */
		virtual void SetSrcY(ControlState controlState, usint srcY);
		
		/**
		 * Sets width of texture region.
		 * @param srcX New width of texture region.
		 */
		virtual inline void SetSrcWidth(usint srcWidth) 
		{ _srcWidth = srcWidth; }
		
		/**
		 * Sets height of texture region.
		 * @param srcX New height of texture region.
		 */
		virtual inline void SetSrcHeight(usint srcHeight) 
		{ _srcHeight = srcHeight; }

	protected:

		usint _srcX[CONTROL_STATE_COUNT];
		usint _srcY[CONTROL_STATE_COUNT];
		usint _srcWidth;
		usint _srcHeight;
};

#endif
