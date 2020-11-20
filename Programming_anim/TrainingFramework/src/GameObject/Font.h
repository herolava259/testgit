#pragma once
#include"GameConfig.h"
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H


class Font
{

public:
	Font(const std::string& font);
	bool		initWithFiles(const std::string& font);
	GLuint		getTextFontAdd();
	GLuint		getArrBuffer();
	FT_Face		getFtFace();
	FT_GlyphSlot getFtGlyph();

	void setName(std::string name) {
		_name = name;
	}
	std::string getName() {
		return _name;
	}
	void setId(GLuint id) {
		_id = id;
	}
	GLuint getId() {
		return _id;
	}

private:
	std::string _name;
	GLuint		_id;
	GLuint		_vboId;
	GLuint		_iTextID;

	FT_Library			_library;
	FT_Face				_face;
	FT_GlyphSlot		_glyphSlot;

};
