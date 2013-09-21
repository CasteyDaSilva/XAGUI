#ifndef XAGUI_FORM_H
#define XAGUI_FORM_H

class Form : public StaticImage
{
	public:

		Form();

		virtual ~Form();

		virtual tinyxml2::XMLError Load(cchar* file);

		virtual void Render();

		virtual inline Texture* GetSkin() const { return StaticImage::GetImage(); }

	public:

		virtual void MouseMoveEvent(int x, int y);

		virtual void MouseButtonEvent(int x, int y, MouseButton button, bool down);
};

#endif