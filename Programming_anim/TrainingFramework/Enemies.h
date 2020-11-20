#pragma once

#include"ActionPlayer.h"
#include"Player.h"
#include"ResourceManagers.h"
enum EnemyTypes {
	ENEMY_Wolf,
	ENEMY_Golbin,
	ENEMY_Bear,
	ENEMY_Ghost,
	ENEMY_Cart 
};
class ActionPlayer;
class Enemies :public Figure {
private:
	GLint m_id;
	std::string m_Name;
protected:
	void Init();
	ImpactEvents m_Event;
	//std::queue<GLint> m_stackKey;
	//std::queue<Vector2> m_queueClick;
	std::map<std::string, std::shared_ptr<Texture>> m_listEffect;
	std::map<std::string, std::shared_ptr<SpriteAnimation>> m_listEffectObj;
	//std::queue<PlayerControls> m_queueControl;
	PlayerControls m_currentControl;
	Vector2 m_direction;
	GLint m_moveLimited;
	//void(*ActionPlayer::m_pAction)();

public:
	Enemies(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture>texture);
	Enemies(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~Enemies();

	GLint GetId();
	std::string GetName();
	void CatchEvent(ImpactEvents impt, GLint next_pos = 0);
	virtual void Move(GLfloat deltaTime) ;

	void Collision(GLint next_pos = 0);
	void Final();
	void Frozen();
	void BeEaten();
	void FallingDown();
	void PickCake();

	void Update(GLfloat deltatime, bool is_allStand);
	//void HandleTouchEvents(GLint pos_x, GLint pos_y, bool isPressed);
	//void HandleKeyEvents(GLint key, bool isPressed);
	GLint abs_value(GLint x);

	void DrawAction();
	
	void ChangeState(GLint next_pos = 0);
	void SetMoveControl(PlayerControls control);

};