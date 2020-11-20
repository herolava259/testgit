#include "Sprite3D.h"
#include "Camera.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"


void Sprite3D::CaculateWorldMatrix()
{
	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	GLfloat tempX = (GLfloat)(m_Vec3Rotation.x * PI * 2 / MAX_DEGREE);
	m_Rx.SetRotationX(tempX);
	GLfloat tempY = (GLfloat)(m_Vec3Rotation.y * PI * 2 / MAX_DEGREE);
	m_Ry.SetRotationY(tempY);
	GLfloat tempZ = (GLfloat)(m_Vec3Rotation.z * PI * 2 / MAX_DEGREE);
	m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position);

	m_WorldMat = m_Sc * m_Rz * m_Rx * m_Ry * m_T;
}

Sprite3D::Sprite3D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Camera> camera, std::shared_ptr<Texture> texture)
	: BaseObject()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = camera;
	m_pTexture = texture;
}

Sprite3D::Sprite3D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Camera> camera, Vector4 color)
	: BaseObject()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = camera;
	m_pTexture = nullptr;
	m_Color = color;
}

Sprite3D::~Sprite3D(void)
{
}


void Sprite3D::Init()
{

	CaculateWorldMatrix();
}

void Sprite3D::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());
	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// All object
	matrixWVP = m_WorldMat * m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);


	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

void Sprite3D::Update(GLfloat deltatime)
{

}


void Sprite3D::Set3DPosition(Vector3 pos)
{
	m_Vec3Position = pos;
	CaculateWorldMatrix();
}
Vector3 Sprite3D::Get3DPosition()
{
	return m_Vec3Position;
}

void Sprite3D::Set3DScale(Vector3 sca)
{
	m_Vec3Scale = sca;
	CaculateWorldMatrix();
}
Vector3 Sprite3D::Get3DScale()
{
	return m_Vec3Scale;
}

void Sprite3D::Set3DRotation(Vector3 ros)
{
	m_Vec3Rotation = ros;
	CaculateWorldMatrix();
}
Vector3 Sprite3D::Get3DRotation()
{
	return m_Vec3Rotation;
}