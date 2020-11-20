#pragma once
#include "utilities.h"

class Shaders 
{
private:
	GLuint		m_iShaderID;
	char		fileVS[260];
	char		fileFS[260];
	GLuint		vertexShader;
	GLuint		fragmentShader;
public:
	Shaders();
	~Shaders();

	GLuint		program;
	GLint		iTextureLoc[5];

	GLint		Init(const std::string& fileVertexShader, const std::string& fileFragmentShader);
	void		EnableTest(GLuint gl_test);
	void		EnableAlpha();

	void		SetShaderID(GLuint id);
	GLuint		GetShaderID();
	GLuint		GetAttribLocation(const std::string& str);
	GLuint		GetUniformLocation(const std::string& str);
};