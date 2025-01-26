#include "TextObject.h"
#include "FontManager.h"

TextObject::TextObject(const string& _text, const string& _path, const FontExtensionType& _fontType)
{
	text = new Text(font, _text);
	M_FONT.Load(this, _path, _fontType);
}

TextObject::TextObject(const TextObject& _other)
{
	text = new Text(*_other.text);
	font = _other.font;
}

TextObject::~TextObject()
{
	delete text;
}