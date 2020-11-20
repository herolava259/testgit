#pragma once
#include"BaseObject.h"
#include"ResourceManagers.h"
#include"SpriteAnimation.h"
typedef struct anim_time {
	GLint numFrame;
	GLfloat timeFrame;
	anim_time(GLint _numFrame, GLfloat _timeFrame) {
		numFrame = _numFrame;
		timeFrame = _timeFrame;
	}

};

//class A : public SpriteAnimation {

//};
class DynamicObject : public BaseObject {
private:
	std::string m_Text;
	void CaculateWorldMatrix();
protected:
	Vector2 m_Vec2DPos;
	GLint m_iHeight;
	GLint m_iWidth;
	GLint m_cur_numFrames;
	GLint m_currentFrame;
	GLfloat m_frameTime;
	GLfloat m_currentTime;
	Vector2 m_Vec2DSpeed;
	std::map<std::string,std::shared_ptr<anim_time>> m_listAnimation;

public:
	DynamicObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~DynamicObject();

	void Init();
	void Draw();
	void Update(GLfloat deltaTime);
	void AddAnimation(std::string& str, GLint numFrames, GLfloat frameTime, bool isUse);
	void SetAnimation(std::string& str);

	void Set2DPostion(GLfloat x, GLfloat y);
	void Set2DPostion(Vector2 vec);

	Vector2 Get2DPostion();
	void SetSize(GLfloat x, GLfloat y);
	Vector2 Get2DSpeed();
};
