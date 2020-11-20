#include "Texture.h"

int Texture::Init(const char *szFileName,GLuint iWapMode,GLuint iFilterMode)
{
	glGenTextures(1,&m_iTextGlId);
	glBindTexture(GL_TEXTURE_2D,m_iTextGlId);

	LOGI("Load 2D Texture:%s\t\t",szFileName);

	GLint h,w,bpp;
	char *imageData = LoadTGA(szFileName,&w,&h,&bpp);
	if(imageData == 0)
	{
		LOGE("ERROR");
		return 0;
	}
	switch (bpp)
	{
	case 24:
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,imageData);
		break;
	case 32:
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
		break;
	}

	if(imageData!=0) delete imageData;

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,iWapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,iWapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,iFilterMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,iFilterMode);

	if((iFilterMode== GL_LINEAR_MIPMAP_LINEAR)||(iFilterMode== GL_LINEAR_MIPMAP_NEAREST)|| (iFilterMode== GL_NEAREST_MIPMAP_LINEAR)||(iFilterMode== GL_NEAREST_MIPMAP_NEAREST))
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);

	LOGI("Done.\n");
	return 0;
}

void Texture::Set2DTextureId(GLuint id)
{
	m_iTextID	= id;
}
GLuint Texture::Get2DTextureId()
{
	return m_iTextID;
}
GLuint Texture::Get2DTextureAdd()
{
	return m_iTextGlId;
}