
#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "Application.h"


GameStateMachine::GameStateMachine()
{
	m_running = true;
	m_pActiveState = 0;
	m_pNextState = 0;
}


GameStateMachine::~GameStateMachine()
{
}


void GameStateMachine::Cleanup()
{
	// cleanup the all states
	while (!m_StatesStack.empty()) {
		m_StatesStack.back()->Exit();
		m_StatesStack.pop_back();
	}
}
class Application;

void GameStateMachine::ChangeState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gstb = GameStateBase::CreateState(stt);
	ChangeState(gstb);
}

void GameStateMachine::ChangeState(std::shared_ptr<GameStateBase> state)
{
	m_pNextState = state;
}


void GameStateMachine::PushState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> state = GameStateBase::CreateState(stt);
	// pause current state
	if (!m_StatesStack.empty()) {
		m_StatesStack.back()->Pause();
	}

	// store and init the new state
	//states.push_back(state);
	//states.back()->Init();
	m_pNextState = state;
}

void GameStateMachine::PopState()
{
	// cleanup the current state
	if (!m_StatesStack.empty()) {
		m_StatesStack.back()->Exit();
		m_StatesStack.pop_back();
	}
	if (!m_StatesStack.empty()) {
		m_pNextState = m_StatesStack.back();
		// resume previous state
		m_pNextState->Resume();
		
	}
	else {
		exit(0);
	}
}

void  GameStateMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		// cleanup the current state
		if (!m_StatesStack.empty()) {
			//m_pActiveState->Exit();
			m_StatesStack.back()->Exit();
			//delete states.back();
			//states.pop_back();
		}
		// store and init the new state
		m_StatesStack.push_back(m_pNextState);
		m_StatesStack.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}