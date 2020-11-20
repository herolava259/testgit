#pragma once
#include"SpriteAnimation.h"
#include"BaseObject.h"
class EffectObject : public SpriteAnimation {
private:
	std::string m_Text;
protected:
	GLint m_numFrametime;
public:
	EffectObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime, GLint numTimes);
	~EffectObject();
	void Update(GLfloat deltatime);
	void SetAnimation(const std::string& str);
	void 
};
