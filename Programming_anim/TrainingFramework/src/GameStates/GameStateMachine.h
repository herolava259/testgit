#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include <list>

class GameStateBase;

enum StateTypes
{
	STATE_INVALID = 0,
	STATE_Intro,
	STATE_Menu,
	STATE_Play,
};

class GameStateMachine : public CSingleton<GameStateMachine>
{

public:
	GameStateMachine();
	~GameStateMachine();


public:

	void Cleanup();

	void ChangeState(std::shared_ptr<GameStateBase> state);
	void ChangeState(StateTypes stt);
	void PushState(StateTypes stt);
	void PopState();

	bool isRunning() { return m_running; }
	void Quit() { m_running = false; }
	void PerformStateChange();

	inline std::shared_ptr<GameStateBase>	CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool		NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool		HasState()const
	{
		return m_StatesStack.size() > 0;
	}

private:

	std::list < std::shared_ptr<GameStateBase>>	m_StatesStack;
	std::shared_ptr<GameStateBase>	m_pActiveState;
	std::shared_ptr<GameStateBase>	m_pNextState;
	bool m_running;
	bool m_fullscreen;
};

