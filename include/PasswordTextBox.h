#ifndef XAGUI_PASSWORD_TEXT_BOX_H
#define XAGUI_PASSWORD_TEXT_BOX_H

class PasswordTextBox : public TextBox
{
	public:

		/**
		 * Constructor
		 */
		PasswordTextBox();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		PasswordTextBox(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~PasswordTextBox();

		/**
		 * Reads properties from a XML file.
		 * @param element Element of XML file.
		 */
		virtual void ReadProperties(tinyxml2::XMLElement* element);

		/**
		 * Removes character on specified position.
		 * @param position Position of character to remove.
		 */
		virtual void RemoveCharacter(int position);

		/**
		 * Returns text of text box.
         * @return Text of text box.
		 */
		virtual inline cchar* GetText() const { return _text.c_str(); }
		
		/**
		 * Returns password char of text box.
         * @return Password char of text box.
		 */
		virtual inline cchar* GetPasswordChar() const { return _passwordChar.c_str(); }

		/**
		 * Sets text of text box.
         * @param text New text of text box.
		 */
		virtual void SetText(cchar* text);

		/**
		 * Sets password char of text box.
         * @param text New password char of text box.
		 */
		virtual inline void SetPasswordChar(cchar* passwordChar) { _passwordChar = passwordChar; }

	public:

		/**
		 * Adds text. It should be called before StartTextInput() and finished by StopTextInput().
		 * @see StartTextInput()
		 * @see StopTextInput()
		 * @param text Typed text.
		 */
		virtual bool TextInputEvent(std::string text);

	protected:

		std::string _text;
		std::string _passwordChar;
};

#endif