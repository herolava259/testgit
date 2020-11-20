#pragma once 
#include "Sprite2D.h"
enum ButtonTypes {
	BUTTON_Invalids = 0,
	BUTTON_Intro,
	BUTTON_Play,
	BUTTON_Resume,
	BUTTON_Mute,
	BUTTON_Close,
	BUTTON_Options
};
class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();

private:
	void	(*m_pBtClick)();
	bool	m_isHandle;

};
