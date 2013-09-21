#ifndef XAGUI_SLIDER_H
#define XAGUI_SLIDER_H

class Slider : public Button
{
	public:

		Slider();

		Slider(tinyxml2::XMLElement* element, Control* parent);

		virtual ~Slider();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void Render();

		virtual inline usint GetMarkerSrcX() const { return _markerSrcX; }

		virtual inline usint GetMarkerSrcY() const { return _markerSrcY; }

		virtual inline usint GetMarkerSrcWidth() const { return _markerSrcWidth; }

		virtual inline usint GetMarkerSrcHeight() const { return _markerSrcHeight; }

		virtual void SetMarkerSrcX(usint markerSrcX);

		virtual void SetMarkerSrcY(usint markerSrcY);

		virtual void SetMarkerSrcWidth(usint markerSrcWidth);

		virtual void SetMarkerSrcHeight(usint markerSrcHeight);

	protected:

		int _value;
		int _minValue;
		int _maxValue;

		usint _markerSrcX;
		usint _markerSrcY;
		usint _markerSrcWidth;
		usint _markerSrcHeight;
};

#endif
