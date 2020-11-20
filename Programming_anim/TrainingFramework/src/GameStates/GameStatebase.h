#pragma once
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"


class GameStateBase
{
public:
	GameStateBase(void){}
	virtual ~GameStateBase(void){}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	virtual void Update(float deltaTime ) = 0;
	virtual void Draw() = 0;
	/*
	void ChangeState(GameStateMachine* game, GameStateBase* state) {
		game->ChangeState(state);
	}*/

	static std::shared_ptr<GameStateBase> CreateState(StateTypes stt);
	

};

