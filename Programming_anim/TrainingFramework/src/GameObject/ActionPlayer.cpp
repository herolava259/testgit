#include"ActionPlayer.h"
#include"Sprite2D.h"
#include"GameConfig.h"
extern GLint screenWidth;
extern GLint screenHeight;

class ActionPlayer;
void ActionPlayer::Init() {
	Player::Init();
	m_Name = "Red Riding Hood Girls";
	m_id = 0;
	m_currentkey = 0;
	m_currPosClick = Vector2(0, 0);
	m_pAction = NULL;
	m_Event = ImpactEvents::IMPACT_Invalids;
	m_direction = Vector2(0.0f, 0.0f);
}
ActionPlayer::ActionPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture>texture) :Player(model, shader, texture){
	
	this->Init();
}

ActionPlayer::~ActionPlayer(){}

GLint ActionPlayer::GetId() {
	return m_id;
}
std::string ActionPlayer::GetName() {
	return m_Name;
}
void ActionPlayer::CatchEvent(ImpactEvents impt, GLint next_pos) {
	m_Event = impt;
	ChangeState(next_pos);
}
class Player;
void ActionPlayer::ChangeState(GLint next_pos =0) {
	auto p = this;
	if (m_Event == ImpactEvents::IMPACT_Invalids) {
		return;
	}
	else if (m_Event == ImpactEvents::IMPACT_Collision) {
		this->SetState(StateFigTypes::FIGURE_Inertia);
		this->Collision(next_pos);
	}
	else if (m_Event == ImpactEvents::IMPACT_Eaten) {
		this->SetState(StateFigTypes::FIGURE_Dead);
		this->BeEaten();
	}
	else if (m_Event == ImpactEvents::IMPACT_Fallingdown) {
		this->SetState(StateFigTypes::FIGURE_Dead);
		this->FallingDown();
	}
	else if (m_Event == ImpactEvents::IMPACT_Final) {
		this->SetState(StateFigTypes::FIGURE_Success);
		this->Final();
	}
	else if (m_Event == ImpactEvents::IMPACT_Frozen) {
		this->SetState(StateFigTypes::FIGURE_Freeze);
		this->Frozen();
	}
	else if (m_Event == ImpactEvents::IMPACT_Pickcake); {
		this->SetState(StateFigTypes::FIGURE_Invalids);
		this->PickCake();
	}
}

void ActionPlayer::Move(GLfloat deltaTime) {
	if (m_Speed != 0) {
		GLfloat x = m_Vec2DPos.x + m_Speed * m_direction.x * deltaTime;
		GLfloat y = m_Vec2DPos.y + m_Speed * m_direction.y * deltaTime;
		Set2DPosition(x, y);
	}
}

GLint ActionPlayer::abs_value(GLint x) {
	return(x > 0 ? x : -x);
}
void ActionPlayer::HandleTouchEvents(GLint pos_x, GLint pos_y, bool IsPressed) {
	if (!IsPressed) {
		GLint x = m_Vec2DPos.x - pos_x;
		GLint y = m_Vec2DPos.y - pos_y;
		if (abs_value(x) > abs_value(y)) {
			if (x < 0) {
				m_queueControl.push(PlayerControls::CONTROL_Left);
			}
			else {
				m_queueControl.push(PlayerControls::CONTROL_Right);
			}
		}
		else {
			if (y < 0) {
				m_queueControl.push(PlayerControls::CONTROL_Down);
			}
			else {
				m_queueControl.push(PlayerControls::CONTROL_Up);
			}
		}
		
	}
}

void ActionPlayer::HandleKeyEvents(GLint key, bool isPressed) {
	if (!isPressed) {
		if (key == KEY_LEFT || key == KEY_MOVE_LEFT) {
			m_queueControl.push(PlayerControls::CONTROL_Left);
		}
		else if (key == KEY_RIGHT || key == KEY_MOVE_RIGHT) {
			m_queueControl.push(PlayerControls::CONTROL_Right);
		}
		else if (key == KEY_UP || key == KEY_MOVE_FORWORD) {
			m_queueControl.push(PlayerControls::CONTROL_Up);
		}
		else if (key == KEY_DOWN || key == KEY_MOVE_BACKWORD) {
			m_queueControl.push(PlayerControls::CONTROL_Down);
		}
	}
}
void ActionPlayer::SetMoveControl(bool isStand) {
	if (isStand) {
		PlayerControls control = m_queueControl.front();
		m_queueControl.pop();
		if (control == PlayerControls::CONTROL_Left) {
			m_direction.x = -1.0;
			m_direction.y = 0.0;
			
		}
		else if (control == PlayerControls::CONTROL_Right) {
			m_direction.x = 1.0;
			m_direction.y = 0.0;
			
		}
		else if (control == PlayerControls::CONTROL_Up) {
			m_direction.x = 0.0;
			m_direction.y = -1.0;
		}
		else if (control == PlayerControls::CONTROL_Down) {
			m_direction.x = 0.0;
			m_direction.y = 1.0;
		}
		SetState(StateFigTypes::FIGURE_Move);
	}
}
void ActionPlayer::Collision(GLint next_pos =0) {
	
}
void ActionPlayer::Final() {

}

void ActionPlayer::Frozen(){}
void ActionPlayer::BeEaten(){}
void ActionPlayer::FallingDown(){}

void ActionPlayer::PickCake(){
	m_numCake++;
}

void ActionPlayer::Update(GLfloat deltaTime, bool is_allStand) {
	
}

