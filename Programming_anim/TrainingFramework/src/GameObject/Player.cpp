#include"Player.h"
#include"Texture.h"
#include"Shaders.h"
#include"SpriteAnimation.h"
#include"Models.h"
#include"Sprite2D.h"
#include"ResourceManagers.h"

extern GLint screenWidth;
extern GLint screenHeight;

class Sprite2D;
class Player;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders>shader, std::shared_ptr<Texture>texture):Sprite2D(model,shader,texture){
	m_pShaderAnim = ResourceManagers::GetInstance()->GetShader("Animation");
	m_numCake = 0;
	m_State = StateFigTypes::FIGURE_Stand;
	m_currentFrame = 0;
	m_currentTime = 0;
	m_Speed = 0;
	m_isChangeState = 0;
}
Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color) :Sprite2D(model, shader, color) {
	m_Id = 1;
	m_Name = "Red Riding Hood girl";
	m_pShaderAnim = ResourceManagers::GetInstance()->GetShader("Animation");
	m_numCake = 0;
	m_State = StateFigTypes::FIGURE_Stand;
	m_currentFrame = 0;
	m_currentTime = 0.0f;
	m_Speed = 0;
	m_isChangeState = 0;
}
Player::~Player() {
}
GLint Player::GetId() {
	return m_Id;
}
std::string Player::GetName() {
	return this->m_Name;
}

void Player::SetName(std::string name) {
	this->m_Name = name;
}
GLint Player::GetnumCake() {
	return m_numCake;
}
void Player::SetnumCake(GLint numCake) {
	m_numCake = numCake;
}

StateFigTypes Player::GetCurrentState() {

	return m_State;
}

void Player::AddState(const std::string& str, StateFigTypes statetype, StateAttribute stateattr = StateAttribute(0, 0.0f, 0.0f, NULL)) {
	std::shared_ptr<Texture> texture = ResourceManagers::GetInstance()->GetTexture(str);
	stateattr.pTextureAnimation = texture;
	m_listState.insert(std::pair<StateFigTypes, const std::string>(statetype, str));
	m_listAttrState.insert(std::pair<std::string, StateAttribute>(str, stateattr));
}
void Player::SetFps(StateFigTypes state, GLint numFrame, GLfloat frameTime, GLfloat speed,bool isLoop, std::shared_ptr<Texture> textureAnimation) {
	auto it = m_listState.find(state);

	if (it == m_listState.end())  return;

	std::string str = it->second;
	m_listAttrState.insert(std::pair<std::string, StateAttribute>(str, StateAttribute(numFrame, frameTime, speed, isLoop, textureAnimation)));
}

void Player::SetState(StateFigTypes state) {
	m_pShader = m_pShaderAnim;
	auto it = m_listState.find(state);

	if (it == m_listState.end())  return;

	std::string str = it->second;
	auto iter = m_listAttrState.find(str);
	if (iter == m_listAttrState.end()) return;
	StateAttribute attr = iter->second;

	m_numFrames = attr.numFrame;
	m_frameTime = attr.frameTime;
	m_Speed = attr.speed;
	m_pTexture = attr.pTextureAnimation;
	m_currentTime = 0.0f;
	m_currentFrame = 0;
	m_isChangeState = 1;
	m_State = state;

}

bool Player::IsChangeState() {
	return m_isChangeState;
}
class SpriteAnimation;
void Player::DrawCurrState() {
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
	//this->Init();

}

void Player::Init(){
	m_numCake = 0;
	m_State = StateFigTypes::FIGURE_Invalids;
	m_numFrames = 0;
	m_currentFrame = 0;
	Sprite2D::Init();
}

void Player::Update(GLfloat deltatime) {
	if (!m_isChangeState) {
		if (m_isLoop || m_currentFrame < m_numFrames) {
			m_currentTime += deltatime;
			if (m_currentTime >= m_frameTime) {
				m_currentFrame++;
				if (m_currentFrame >= m_numFrames)
					m_currentFrame = 0;
				m_currentTime -= m_frameTime;
			}
		}
	}
	else {
		m_isChangeState = 0;
		m_currentTime = 0.0f;
		m_currentFrame = 0;
	}
}