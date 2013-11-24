#ifndef XAGUI_FORM_H
#define XAGUI_FORM_H

class Form : public PictureBox
{
	public:

		/**
		 * Constructor
		 */
		Form();

		/**
		 * Destructor
		 */
		virtual ~Form();

		/**
		 * Loads form from XML file.
		 * @param file Path to XML file.
		 */
		virtual tinyxml2::XMLError Load(cchar* file);
		
		/**
		 * Loads form from buffer.
		 * @param buffer Buffer with xml file data.
		 */
		virtual tinyxml2::XMLError LoadFromMemory(cchar* buffer);
		
		/**
		 * Renders control.
		 */
		virtual void Render();

		/**
		 * Returns form skin.
		 * @return Form skin.
		 */
		virtual inline Texture* GetSkin() const { return PictureBox::GetImage(); }
};

#endif