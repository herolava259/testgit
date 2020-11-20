#pragma once
#include"GameButton.h"
#include"BaseObject.h"
#include"SpriteAnimation.h"
#include"Sprite2D.h"
#include<map>


class OptWinObject : public BaseObject {
private:
	std::string  m_Text;
	void CaculateWorldMatrix();
	std::map <std::string,std::shared_ptr<GameButton>> m_listButton;
protected: 
	

	std::shared_ptr<Texture> m_bgWindow;
	Vector2 m_Vec2DPos;
	GLint m_iHeight;
	GLint m_iWidth;
	// thuoc tinh cua animation 
	GLint m_numFrames;
	GLint m_currentFrame;
	GLfloat m_frameTime;
	GLfloat m_frameTime;
	GLfloat m_currentTime;
public:
	OptWinObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~OptWinObject();

	void Init() override;
	void Draw() final;

	void Draw_button();

	void Draw_background();
	void Draw_Animation();
	void Update(GLfloat deltatime);

	void SetBackGround(const std::string& str);

	void AddButton(const std::string str,  GLint width, GLint height,GLfloat x_pos, GLfloat y_pos, void(*pBtClick)() = NULL );
	std::shared_ptr<GameButton> GetButton(const std::string& str);

	void Set2DPostion(GLfloat x, GLfloat y);
	void Set2DPostion(Vector2 vec);

	Vector2 Get2DPostion();
	void SetSize(GLint width, GLint height);
};