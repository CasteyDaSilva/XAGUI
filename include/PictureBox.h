#ifndef XAGUI_PICTURE_BOX_H
#define XAGUI_PICTURE_BOX_H

class PictureBox : public Button
{
	public:

		/**
		 * Constructor
		 */
		PictureBox();

		/**
		 * Constructor
		 * @param element Element of XML file.
		 * @param parent Parent control.
		 */
		PictureBox(tinyxml2::XMLElement* element, Control* parent);
		
		/**
		 * Destructor
		 */
		virtual ~PictureBox();

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
		 * Deletes texture object.
		 */
		virtual void DeleteTexture();

		/**
		 * Return image.
		 * @return Pointer to texture object.
		 */
		virtual inline Texture* GetImage() const { return _image; }
		
		/**
		 * Sets image.
		 * @param image Pointer to texture object.
		 */
		virtual inline void SetImage(Texture* image) { _image = image; }


	protected:

		Texture* _image;
};

#endif