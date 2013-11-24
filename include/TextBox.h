#ifndef XAGUI_TEXT_BOX_H
#define XAGUI_TEXT_BOX_H

class TextBox : public Button
{
	public:

		/**
		 * Constructor
		 */
		TextBox();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		TextBox(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~TextBox();

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
		 * Inserts text on specified position.
		 * @param text Text to be added.
		 * @param position Position to add for text.
		 */
		virtual void InsertText(cchar* text, int position);

		/**
		 * Removes character on specified position.
		 * @param position Position of character to remove.
		 */
		virtual void RemoveCharacter(int position);

		/**
		 * Returns text of text box.
         * @return Text of text box.
		 */
		virtual inline cchar* GetText() const { return _label->GetText(); }

		/**
		 * Returns current position of caret.
         * @return Current position of caret.
		 */
		virtual inline uint GetCaretPosition() const { return _caretPosition; }
		
		/**
		 * Returns absolute X position of caret.
         * @return Absolute X position of caret.
		 */
		virtual inline sint GetCaretPositionX() const { return _caretPositionX; }
		
		/**
		 * Returns absolute Y position of caret.
         * @return Absolute Y position of caret.
		 */
		virtual inline sint GetCaretPositionY() const { return _caretPositionY; }

		/**
		 * Returns X position of texture region of caret.
		 * @return X position of texture region of caret.
		 */
		virtual inline usint GetCaretSrcX() const { return _caretSrcX; }
		
		/**
		 * Returns Y position of texture region of caret.
		 * @return Y position of texture region of caret.
		 */
		virtual inline usint GetCaretSrcY() const { return _caretSrcY; }

		/**
		 * Returns width of texture region of caret.
		 * @return width of texture region of caret.
		 */
		virtual inline usint GetCaretSrcWidth() const { return _caretSrcWidth; }

		/**
		 * Returns height of texture region of caret.
		 * @return height of texture region of caret.
		 */
		virtual inline usint GetCaretSrcHeight() const { return _caretSrcHeight; }

		/**
		 * Sets text of text box.
         * @param text New text of text box.
		 */
		virtual void SetText(cchar* text);

		/**
		 * Sets position of caret.
		 * @param position New position of caret.
		 */
		virtual void SetCaretPosition(int position);
		
		/**
		 * Sets X position of texture region of caret.
		 * @param caretSrcX New X position of texture region of caret.
		 */
		virtual inline void SetCaretSrcX(usint caretSrcX) { _caretSrcX = caretSrcX; }

		/**
		 * Sets Y position of texture region of caret.
		 * @param caretSrcY New Y position of texture region of caret.
		 */
		virtual inline void SetCaretSrcY(usint caretSrcY) { _caretSrcY = caretSrcY; }

		/**
		 * Sets width of texture region of caret.
		 * @param caretSrcWidth New width of texture region of caret.
		 */
		virtual inline void SetCaretSrcWidth(usint caretSrcWidth) { _caretSrcWidth = caretSrcWidth; }

		/**
		 * Sets height of texture region of caret.
		 * @param caretSrcHeight New height of texture region of caret.
		 */
		virtual inline void SetCaretSrcHeight(usint caretSrcHeight) { _caretSrcHeight = caretSrcHeight; }

	public:

		/**
		 * Moves caret to mouse position when mouse button is pressed.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 */
		virtual Control* MouseButtonDownEvent(int x, int y, uchar button);
		
		/**
		 * Does some action due to pressed key.
		 * @param key Pressedd key.
		 */
		virtual void OnKeyDownEvent(SDL_Scancode key);

		/**
		 * Adds text. It should be called before StartTextInput() and finished by StopTextInput().
		 * @see StartTextInput()
		 * @see StopTextInput()
		 * @param text Typed text.
		 */
		virtual bool TextInputEvent(std::string text);

		/**
		 * Called when control gets focus.
		 */
		virtual void OnGotFocus();

		/**
		 * Called when control lost focus.
		 */
		virtual void OnLostFocus();

	public:

		OnTextInput onTextInput;

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