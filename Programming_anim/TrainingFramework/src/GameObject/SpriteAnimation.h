#pragma once
#include "BaseObject.h"

class SpriteAnimation : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;

public:
	SpriteAnimation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);	
	~SpriteAnimation();

	void		Init() override;
	void		Draw() final;
	virtual void		Update(GLfloat deltatime) override;
	void        SetAnimation(std::string& str);

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);
};

