#ifndef XAGUI_PROGGRESS_BAR_H
#define XAGUI_PROGGRESS_BAR_H

class ProggressBar : public Button
{
	public:

		ProggressBar();

		ProggressBar(tinyxml2::XMLElement* element, Control* parent);

		virtual ~ProggressBar();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual inline uchar GetProggress() const { return _proggress; }
		
		virtual inline usint GetProggressWidth() const { return _proggressWidth; }

		virtual void SetProggress(uchar proggress);

		virtual void SetProggressWidth(usint proggressWidth);

	protected:

		virtual void Render();

	protected:

		uchar _proggress;
		usint _proggressWidth;
};

#endif