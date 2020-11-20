#include "Font.h"
#include "GameConfig.h"



Font::Font(const std::string& font)
{
	initWithFiles(font);
}

bool Font::initWithFiles(const std::string& font)
{
	std::string _font =font;

	if (FT_Init_FreeType(&_library))
	{
		printf("Could not init freetype library\n");
		return false;
	}

	if (FT_New_Face(_library, _font.c_str(), 0, &_face)) {
		printf("Could not open font %s\n", font.c_str());
		return false;
	}
	FT_Set_Pixel_Sizes(_face, 0, 48);
	_glyphSlot = _face->glyph;

	glGenTextures(1, &_iTextID);
	glBindTexture(GL_TEXTURE_2D, _iTextID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filterMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filterMode);

	if((filterMode== GL_LINEAR_MIPMAP_LINEAR)||(filterMode== GL_LINEAR_MIPMAP_NEAREST)|| (filterMode== GL_NEAREST_MIPMAP_LINEAR)||(filterMode== GL_NEAREST_MIPMAP_NEAREST))
	glGenerateMipmap(GL_TEXTURE_2D);
	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &_vboId);
	return true;
}


GLuint Font::getTextFontAdd()
{
	return _iTextID;
}

GLuint Font::getArrBuffer()
{
	return _vboId;
}

FT_Face Font::getFtFace() {
	return _face;
}

FT_GlyphSlot Font::getFtGlyph() {
	return _glyphSlot;
}