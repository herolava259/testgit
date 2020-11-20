#pragma once
#include "GameConfig.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector3 bitangent;
	Vector3 tangent;
	Vector2 uv;
};

class Models
{
private:
	GLuint		m_iModelID;
	GLuint		m_iNumIndices;
	GLuint		m_iVboID; 
	GLuint		m_iIboID;
public:
	Models(const std::string& fileName, GLuint type);
	~Models();
	GLuint		GetVertexObject();
	GLuint		GetIndiceObject();
	GLuint		GetNumIndiceObject();
	void		SetModelId(GLuint id);
	GLuint		GetModelId();
};