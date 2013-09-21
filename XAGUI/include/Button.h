#ifndef XAGUI_BUTTON_H
#define XAGUI_BUTTON_H

class Button : public Control
{
	public:

		Button();

		Button(tinyxml2::XMLElement* element, Control* parent);

		virtual ~Button();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void Render();

		virtual inline usint GetSrcX(ControlState controlState) const { return _srcX[controlState]; }

		virtual inline usint GetSrcY(ControlState controlState) const { return _srcY[controlState]; }

		virtual inline usint GetSrcWidth(ControlState controlState) const 
		{ return _srcWidth[controlState]; }

		virtual inline usint GetSrcHeight(ControlState controlState) const 
		{ return _srcHeight[controlState]; }

		virtual void SetSrcX(usint srcX);

		virtual void SetSrcY(usint srcY);

		virtual void SetSrcWidth(usint srcWidth);

		virtual void SetSrcHeight(usint srcHeight);

		virtual void SetSrcHoverX(usint srcHoverX);

		virtual void SetSrcHoverY(usint srcHoverY);

		virtual void SetSrcHoverWidth(usint srcHoverWidth);

		virtual void SetSrcHoverHeight(usint srcHoverHeight);

		virtual void SetSrcPressedX(usint srcPressedX);

		virtual void SetSrcPressedY(usint srcPressedY);

		virtual void SetSrcPressedWidth(usint srcPressedWidth);

		virtual void SetSrcPressedHeight(usint srcPressedHeight);

		virtual void SetSrcDisabledX(usint srcDisabledX);

		virtual void SetSrcDisabledY(usint srcDisabledY);

		virtual void SetSrcDisabledWidth(usint srcDisabledWidth);

		virtual void SetSrcDisabledHeight(usint srcDisabledHeight);

	protected:

		usint _srcX[CONTROL_STATE_COUNT];
		usint _srcY[CONTROL_STATE_COUNT];
		usint _srcWidth[CONTROL_STATE_COUNT];
		usint _srcHeight[CONTROL_STATE_COUNT];
};

#endif
