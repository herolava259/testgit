#pragma once
#include"Player.h"
#include"Sprite2D.h"
#include"SpriteAnimation.h"
#include"ResourceManagers.h"
#include<queue>

extern GLint screenWidth;
extern GLint screenHeight;
enum ImpactEvents {
	IMPACT_Invalids = 0,
	IMPACT_Collision,
	IMPACT_Fallingdown,
	IMPACT_Final,
	IMPACT_Pickcake,
	IMPACT_Eaten,
	IMPACT_Frozen,
	IMPACT_Stop,
	IMPACT_Inertia

};
enum PlayerControls {
     CONTROL_Right,
	 CONTROL_Left,
	 CONTROL_Up,
	 CONTROL_Down
};
class Player;
class Sprite2D;
class SpriteAnimation;
class ActionPlayer : public Player {
private:
	GLint m_id;
	std::string m_Name;

protected:
	GLint m_currentkey;
	Vector2 m_currPosClick;
	ImpactEvents m_Event;
	//std::queue<GLint> m_stackKey;
	//std::queue<Vector2> m_queueClick;
	std::map<std::string, std::shared_ptr<Texture>> m_listEffect;
	std::map<std::string, std::shared_ptr<SpriteAnimation>> m_listEffectObj;
	std::queue<PlayerControls> m_queueControl;
	PlayerControls m_currentControl;
	Vector2 m_direction;
	void(*ActionPlayer::m_pAction)();
public:
	ActionPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture>texture );
	ActionPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~ActionPlayer();

	GLint GetId();
	std::string GetName();
	void CatchEvent(ImpactEvents impt, GLint next_pos = 0);

	void Move(GLfloat deltaTime);
	void Collision(GLint next_pos =0);
	void Final();
	void Frozen();
	void BeEaten();
	void FallingDown();
	void PickCake();

	void Update(GLfloat deltatime, bool is_allStand);
	void HandleTouchEvents(GLint pos_x, GLint pos_y, bool isPressed);
	void HandleKeyEvents(GLint key, bool isPressed);
	GLint abs_value(GLint x);

	void AdapterControls();

	void DrawAction();
	void Init();
	void ChangeState(GLint next_pos =0);
	void SetMoveControl(bool isMove);

};