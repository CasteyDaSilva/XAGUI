#ifndef XAGUI_CHECK_BOX_H
#define XAGUI_CHECK_BOX_H

class CheckBox : public Button
{
	public:

		CheckBox();

		CheckBox(tinyxml2::XMLElement* element, Control* parent);

		virtual ~CheckBox();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void OnClickEvent();

		virtual inline bool IsChecked() const { return _checked; }

		virtual inline usint GetSrcCheckedX(ControlState controlState) const 
		{ return _srcCheckedX[controlState]; }

		virtual inline usint GetSrcCheckedY(ControlState controlState) const 
		{ return _srcCheckedY[controlState]; }

		virtual inline usint GetSrcCheckedWidth(ControlState controlState) const 
		{ return _srcCheckedWidth[controlState]; }

		virtual inline usint GetSrcCheckedHeight(ControlState controlState) const 
		{ return _srcCheckedHeight[controlState]; }

		virtual void SetSrcCheckedX(usint srcCheckedX);

		virtual void SetSrcCheckedY(usint srcCheckedY);

		virtual void SetSrcCheckedWidth(usint srcCheckedWidth);

		virtual void SetSrcCheckedHeight(usint srcCheckedHeight);

		virtual void SetSrcCheckedHoverX(usint srcCheckedHoverX);

		virtual void SetSrcCheckedHoverY(usint srcCheckedHoverY);

		virtual void SetSrcCheckedHoverWidth(usint srcCheckedHoverWidth);

		virtual void SetSrcCheckedHoverHeight(usint srcCheckedHoverHeight);

		virtual void SetSrcCheckedPressedX(usint srcCheckedPressedX);

		virtual void SetSrcCheckedPressedY(usint srcCheckedPressedY);

		virtual void SetSrcCheckedPressedWidth(usint srcCheckedPressedWidth);

		virtual void SetSrcCheckedPressedHeight(usint srcCheckedPressedHeight);

		virtual void SetSrcCheckedDisabledX(usint srcCheckedDisabledX);

		virtual void SetSrcCheckedDisabledY(usint srcCheckedDisabledY);

		virtual void SetSrcCheckedDisabledWidth(usint srcCheckedDisabledWidth);

		virtual void SetSrcCheckedDisabledHeight(usint srcCheckedDisabledHeight);

	protected:

		virtual void Render();

	protected:

		usint _srcCheckedX[CONTROL_STATE_COUNT];
		usint _srcCheckedY[CONTROL_STATE_COUNT];
		usint _srcCheckedWidth[CONTROL_STATE_COUNT];
		usint _srcCheckedHeight[CONTROL_STATE_COUNT];

		bool _checked;
};

#endif