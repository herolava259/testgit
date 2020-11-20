#include"StaticObject.h"
#include"ResourceManagers.h"
#include"Texture.h"


class StaticObject;
StaticObject::StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime):SpriteAnimation(model, shader, texture, numFrames, frameTime) {
	Init();
}
//StaticObject::StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
StaticObject::~StaticObject() {
}

GLint StaticObject:: GetId() {
	return m_id;
}
std::string StaticObject::GetName()
{

	return this->m_Name;
}
void StaticObject::SetId(GLint id) {
	m_id = id;
}

void StaticObject::SetName(std::string name) {

	m_Name = name;
}
StateStaticTypes StaticObject::GetCurrentState() {
	return m_State;
}

void StaticObject::AddState(const std::string& str, StateStaticTypes statetype, StateStaticAttribute stateattr = StateStaticAttribute(true, NULL)) {
	std::shared_ptr<Texture> texture = ResourceManagers::GetInstance()->GetTexture(str);
	stateattr.pTextureAnimation = texture;
	m_listState.insert(std::pair<StateStaticTypes, const std::string>(statetype, str));
	m_listAttrState.insert(std::pair<std::string, StateStaticAttribute>(str, stateattr));
}
void StaticObject::SetAnimation(StateStaticTypes state, bool isLoop, std::shared_ptr<Texture> textureAnimation) {
	auto it = m_listState.find(state);

	if (it == m_listState.end())  return;

	std::string str = it->second;
	m_listAttrState.insert(std::pair<std::string, StateStaticAttribute>(str, StateStaticAttribute(isLoop, textureAnimation)));
}

void StaticObject::SetState(StateStaticTypes state) {
	
	auto it = m_listState.find(state);

	if (it == m_listState.end())  return;
	
	std::string str = it->second;
	auto iter = m_listAttrState.find(str);
	if (iter == m_listAttrState.end()) return;
	StateStaticAttribute attr = iter->second;

	m_pTexture = attr.pTextureAnimation;
	m_currentTime = 0.0f;
	m_currentFrame = 0;
	m_isChangeState = 1;
	m_State = state;
}
bool StaticObject::IsChangeState() {
	return m_isChangeState;
}

void DrawCurrState();
void StaticObject::Updated(GLfloat deltatime) {
	if (!m_isChangeState) {
		if (m_isLoop || m_currentFrame < m_numFrames) {
			m_currentTime += deltatime;
			if (m_currentTime >= m_frameTime) {
				m_currentFrame++;
				if (m_currentFrame >= m_numFrames)
					m_currentFrame = 0;
				m_currentTime -= m_frameTime;
			}
			else {
				if (m_State == StateStaticTypes::STATIC_Vibrate) {
					SetState(StateStaticTypes::STATIC_Silent);
				}
				
			}
		}
	}
	else {
		m_isChangeState = 0;
		m_currentTime = 0.0f;
		m_currentFrame = 0;
	}
}
void Init();