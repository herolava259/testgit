#pragma once
#include "BaseObject.h"

enum class TEXT_COLOR {
	WHILE = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	BLACK
};

class Font;

class Text : public BaseObject
{
public:
	Text(std::shared_ptr<Shaders> sha, std::shared_ptr<Font> font, std::string text, TEXT_COLOR color, float size);
	~Text();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;
	void		setFont(std::shared_ptr<Font> font);
	void		setText(std::string text);

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);
private:
	std::string				m_text;
	std::shared_ptr<Font>	m_font;

	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	Vector2	m_scale;
	Vector4 EnumToVector(TEXT_COLOR color);
	void CaculateWorldMatrix();
};
