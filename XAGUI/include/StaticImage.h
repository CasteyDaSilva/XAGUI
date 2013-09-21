#ifndef XAGUI_STATIC_IMAGE_H
#define XAGUI_STATIC_IMAGE_H

class StaticImage : public Button
{
	public:

		StaticImage();

		StaticImage(tinyxml2::XMLElement* element, Control* parent);

		virtual ~StaticImage();

		virtual void ParseProperties(tinyxml2::XMLElement* element);

		virtual void DeleteTexture();

		virtual inline Texture* GetImage() const { return _image; }

		virtual void SetImage(Texture* image);

	protected:

		virtual void Render();

	protected:

		Texture* _image;
};

#endif