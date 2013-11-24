#ifndef XAGUI_LABEL_H
#define XAGUI_LABEL_H

class Label : public Control
{
	public:

		/**
		 * Constructor
		 */
		Label();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		Label(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~Label();

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
		 * Returns text of label.
         * @return Text of label.
		 */
		virtual inline cchar* GetText() const { return _staticText->Get(); }
		
		/**
		 * Returns static text.
         * @return Static text.
		 */
		virtual inline StaticText* GetStaticText() const { return _staticText; }
		 
		/**
		 * Sets text of label.
		 * @param text New text.
		 */
		virtual void SetText(cchar* text);
		
		/**
		 * Sets text for this label to display with new font and font's size.
		 * @param file Path to font file.
		 * @param size Size of font.
		 * @param text Text to display.
		 */
		virtual void SetText(cchar* file, usint size, cchar* text);
		
		/**
		 * Sets width of label to text width.
		 * @param width Width of label.
		 */
		virtual void SetWidth(usint width);
		
		/**
		 * Sets width of label to text height.
		 * @param height Height of label.
		 */
		virtual void SetHeight(usint height);
		
		/**
		 * Sets color of text.
		 * @param controlState State of control.
		 * @param red Value for red channel of color.
		 * @param green Value for green channel of color.
		 * @param blue Value for blue channel of color.
		 * @param alpha Value for alpha channel of color.
		 */
		virtual void SetColor(ControlState controlState, uchar red, uchar green, uchar blue, uchar alpha);
		
		virtual void SetColor(ControlState controlState, SDL_Color color);

	protected:

		StaticText* _staticText;
};

#endif
