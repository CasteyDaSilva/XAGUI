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
		 * Renders control.
		 */
		virtual void Render();

		/**
		 * Returns form skin.
		 * @return Form skin.
		 */
		virtual inline Texture* GetSkin() const { return PictureBox::GetImage(); }

	public:

		/**
		 * Sends mouse move event to all children.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 */
		virtual void MouseMoveEvent(int x, int y);

		/**
		 * Sends mouse button event to all children.
		 * @param x X position of mouse.
		 * @param y Y position of mouse.
		 * @param button Pressed mouse button.
		 * @param down Whether is pressed button.
		 */
		virtual bool MouseButtonEvent(int x, int y, MouseButton button, bool down);
};

#endif