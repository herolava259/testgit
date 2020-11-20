#include"DynamicObject.h"

#include"Shaders.h"
#include"Models.h"
#include"Texture.h"

#include"ResourceManagers.h"

#include"SpriteAnimation.h"


extern GLint screenWidth;
extern GLint screenHeight;



DynamicObject::DynamicObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime):BaseObject() {
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	
	m_cur_numFrames = numFrames;
	m_frameTime = frameTime;

	m_currentFrame = 0;
	m_currentTime = 0.0f;

	m_Vec3Position = Vector3(0, 0, 0);
	m_Vec2DSpeed = Vector2(0.0, 0.0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

DynamicObject::~DynamicObject() {

}
void DynamicObject::CaculateWorldMatrix() {
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_Sc.SetTranslation(m_Vec3Position);
	m_WorldMat = m_Sc * m_T;
	
}
void DynamicObject::Init() {
	CaculateWorldMatrix();
}

class A : public SpriteAnimation {

};

void DynamicObject::Draw() {
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

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
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
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

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_cur_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/*void Update();
	void SetAnimation(std::string& str, GLint numFrames, GLfloat frameTime, bool isUse);
	void UseAnimation(std::string& str);

	void Set2DPostion(GLint x, GLint y);
	void Set2DPostion(Vector2 vec);

	Vector2 Get2DPostion();
	void setSize(GLint x, GLint y);*/


void DynamicObject::Update(GLfloat deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame > m_cur_numFrames) {
			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}
}

void DynamicObject::SetAnimation(std::string& str) {
	auto it = ResourceManagers::GetInstance()->GetTexture(str);
	//anim_time at;
	if (it != NULL) {
		m_pTexture = it;
	    auto ptime = m_listAnimation.find(str)->second;
		m_cur_numFrames = ptime->numFrame;
		m_frameTime = ptime->timeFrame;
	}
	//Draw();
}
void DynamicObject::AddAnimation(std::string& str, GLint numFrames, GLfloat frameTime, bool isUse) {
	auto it = ResourceManagers::GetInstance()->GetTexture(str);
	
	if (it != NULL) {
		m_listAnimation.insert(std::pair<std::string,std::shared_ptr<anim_time>>(str, std::make_shared<anim_time>(numFrames, frameTime)));
	}
	if (isUse) {
		SetAnimation(str);
	}
	
}

void DynamicObject::Set2DPostion(GLfloat x, GLfloat y) {
	m_Vec2DPos.x = x;
	m_Vec2DPos.y = y;
	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);
	CaculateWorldMatrix();
}

void DynamicObject::Set2DPostion(Vector2 vec) {
	m_Vec2DPos = vec;
	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);
	CaculateWorldMatrix();
}

Vector2 DynamicObject::Get2DPostion() {
	return m_Vec2DPos;
}
Vector2 DynamicObject::Get2DSpeed() {
	return m_Vec2DSpeed;
}

void DynamicObject::SetSize(GLfloat x, GLfloat y) {
	m_iHeight = x;
	m_iWidth = y;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
	CaculateWorldMatrix();
}