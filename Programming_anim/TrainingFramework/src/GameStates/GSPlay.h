#pragma once
#include "gamestatebase.h"
#include "StaticObject.h"
#include "ActionPlayer.h"
#include "EffectObject.h"
#include "Enemies.h"
#include "EnemiesManagers.h"
#include "OptWinObject.h"

//class Enemies;
//class StaticObject;

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::shared_ptr<ActionPlayer> m_Player;
	std::vector <std::shared_ptr<OptWinObject>> m_listSubWin;
	std::vector<std::shared_ptr<GameButton>> m_listButton;
	//std::vector<std::shared_ptr<Enemies>> m_listEnemies;
	//std::vector<std::shared_ptr<StaticObject>> m_listEnemies;
	//std::vector<std::shared_ptr<

};

