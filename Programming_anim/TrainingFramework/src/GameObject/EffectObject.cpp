#include"EffectObject.h"

#include"Texture.h"
#include"Shaders.h"
#include"Camera.h"
#include"Models.h"
#include"ResourceManagers.h"
#include"SpriteAnimation.h"

class A : public SpriteAnimation{};
class EffectObject;
EffectObject::EffectObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat  frameTime, GLint numTimes = 1):SpriteAnimation(model,shader,  texture,numFrames, frameTime){
	m_numFrametime = numFrames;
}

void EffectObject::Update(GLfloat deltatime) {
	m_currentTime += deltatime;
	if (m_numFrametime != 0 && m_currentTime >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames) {
			m_numFrametime = 0;
			m_numFrametime--;
		}
	}
}

void EffectObject::SetAnimation(const std::string& str) {
	m_Text = str;
	this->m_pTexture = ResourceManagers::GetInstance()->GetTexture(str);
}
