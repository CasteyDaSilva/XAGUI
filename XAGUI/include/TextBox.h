#ifndef XAGUI_TEXT_BOX_H
#define XAGUI_TEXT_BOX_H

class TextBox : public Button
{
	public:

		TextBox();

		TextBox(tinyxml2::XMLElement* element, Control* parent);

		virtual ~TextBox();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void Render();

		virtual void RemoveCharacter(int position);

		virtual void KeyEvent(Key key, bool down);

		virtual void TextInputEvent(std::string text);

		virtual inline cchar* GetText() const { return _label->GetText()->Get(); }

		virtual inline uint GetCaretPosition() const { return _caretPosition; }

		virtual inline sint GetCaretPositionX() const { return _caretPositionX; }

		virtual inline sint GetCaretPositionY() const { return _caretPositionY; }

		virtual inline usint GetCaretSrcX() const { return _caretSrcX; }

		virtual inline usint GetCaretSrcY() const { return _caretSrcY; }

		virtual inline usint GetCaretSrcWidth() const { return _caretSrcWidth; }

		virtual inline usint GetCaretSrcHeight() const { return _caretSrcHeight; }

		virtual void SetText(cchar* text);

		virtual void SetCaretPosition(int position);

		virtual void SetCaretSrcX(usint caretSrcX);

		virtual void SetCaretSrcY(usint caretSrcY);

		virtual void SetCaretSrcWidth(usint caretSrcWidth);

		virtual void SetCaretSrcHeight(usint caretSrcHeight);

	public:
		
		virtual void OnMouseButtonEvent(int x, int y, MouseButton button, bool down);
		
		virtual void OnGetFocus();

	protected:

		Label* _label;
		uint _caretPosition;
		sint _caretPositionX;
		sint _caretPositionY;

		usint _caretSrcX;
		usint _caretSrcY;
		usint _caretSrcWidth;
		usint _caretSrcHeight;
};

#endif