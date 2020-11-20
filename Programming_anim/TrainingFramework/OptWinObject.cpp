#include"OptWinObject.h"
#include"ResourceManagers.h"
#include"Texture.h"
#include"Shaders.h"
#include"Models.h"
#include"GameButton.h"
#include"SpriteAnimation.h"



//class B: public OptWinObject{};
extern GLint screenWidth;
extern GLint screenHeight;

//Xay dung cac lop giong SpriteAnimation 

void OptWinObject::CaculateWorldMatrix() {
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);
	m_WorldMat = m_Sc * m_T;
}


void OptWinObject::Init() {
	this->CaculateWorldMatrix();
}

// Xem lai dinh nghia ham khoi tao  
OptWinObject::OptWinObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime):BaseObject() {
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_numFrames = numFrames;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentTime = 0.0f;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}
void OptWinObject::Draw() {
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
		glUniform1f(iTempShaderVaribleGLID, m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OptWinObject::Draw_background() {
	m_pShader = ResourceManagers::GetInstance()->GetShader("TextureShader");
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



	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void OptWinObject::Draw_button() {
	for (auto it : m_listButton) {
		it.second->Draw();
	}
}

void OptWinObject::Update(GLfloat deltatime) {
	m_currentTime += deltatime;
	if (m_currentFrame <= m_numFrames) {
		
		if (m_currentTime >= m_frameTime) {
			m_currentFrame++;
			m_currentTime -= m_frameTime;
		}
	}
	else {
		this->m_pTexture = this->m_bgWindow;
		this->Draw_background();
		this->Draw_button();
	}
}
void OptWinObject::Draw_Animation() {
	if (m_currentFrame <= m_numFrames) {
		this->Draw();
	}
}
//class OptWinObject; 
//class A : public SpriteAnimation {};
void OptWinObject::SetBackGround(const std::string& str) {
	auto background = ResourceManagers::GetInstance()->GetTexture(str);
}

void OptWinObject::AddButton(const std::string str, GLint width, GLint height, GLfloat x_pos, GLfloat y_pos, void(*pbtClick)() = NULL) {
	auto bShader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto bTexture = ResourceManagers::GetInstance()->GetTexture(str);
	auto bModel = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto button = std::make_shared<GameButton>(bModel, bShader, bTexture);
	button->SetSize(width, height);
	button->Set2DPosition(x_pos, y_pos);
	button->SetOnClick(pbtClick);
	m_listButton.insert(std::pair<std::string, std::shared_ptr<GameButton>>(str, button));
}
std::shared_ptr<GameButton> OptWinObject::GetButton(const std::string& str) {
	return m_listButton.find(str)->second;
}

void OptWinObject::Set2DPostion(GLfloat x, GLfloat y) {
	this->m_Vec2DPos.x = x;
	this->m_Vec2DPos.y = y;
	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	this->m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();

}
void OptWinObject::Set2DPostion(Vector2 vec) {
	m_Vec2DPos = vec;

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

Vector2 OptWinObject::Get2DPostion() {
	return m_Vec2DPos;
}

void OptWinObject::SetSize(GLint width, GLint height) {
	m_iWidth = width;
	m_iWidth = height;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
	CaculateWorldMatrix();
}