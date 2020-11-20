#pragma once
#include "utilities.h" 



class Texture
{
	GLuint		m_iTextGlId;
	GLuint		m_iTextID;
public:
	int			Init(const char *szFileName,GLuint wapMode,GLuint filterMode);
	void		Set2DTextureId(GLuint);
	GLuint		Get2DTextureId();
	GLuint		Get2DTextureAdd();
};
