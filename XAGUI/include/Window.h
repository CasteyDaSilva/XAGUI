#ifndef XAGUI_WINDOW_H
#define XAGUI_WINDOW_H

class Window : public Button
{
	public:

		Window();

		Window(tinyxml2::XMLElement* element, Control* parent);

		virtual ~Window();

		virtual void ParseProperties(tinyxml2::XMLElement* element);
		
		virtual void Render();

	protected:

};

#endif