#include"Enemies.h"

#include"ActionPlayer.h"
#include"Sprite2D.h"
#include"GameConfig.h"
extern GLint screenWidth;
extern GLint screenHeight;

class ActionPlayer;
void Enemies::Init() {
	Figure::Init();
	m_Name = "I'am is the big enemies of you";
	m_id = 1;
	//m_currentkey = 0;
	//m_currPosClick = Vector2(0, 0);
	//m_pAction = NULL;
	m_Event = ImpactEvents::IMPACT_Invalids;
	m_direction = Vector2(0.0f, 0.0f);
}
Enemies::Enemies(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture>texture) :Figure(model, shader, texture) {

	this->Init();
}
Enemies::Enemies(std::shared_ptr<Models> model, std::shared_ptr<Shaders>shader, Vector4 color) : Figure(model, shader, color) {
	this->Init();
}
Enemies::~Enemies() {}

GLint Enemies::GetId() {
	return m_id;
}
std::string Enemies::GetName() {
	return m_Name;
}
void Enemies::CatchEvent(ImpactEvents impt, GLint next_pos = 0) {
	m_Event = impt;
	ChangeState(next_pos);
}
class Figure;
void Enemies::ChangeState(GLint next_pos = 0) {
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

void Enemies::Move(GLfloat deltaTime) {
	if (m_Speed != 0) {
		if (m_direction.x == 0.0f) {
			if ((m_moveLimited - m_Vec2DPos.y) * m_direction.y * m_moveLimited >= 0) {

				GLfloat y = m_Vec2DPos.y + m_Speed * m_direction.y * deltaTime;
				Set2DPosition(m_Vec2DPos.x, y);
			}
			else {
				if (m_State == StateFigTypes::FIGURE_Inertia) {
					SetState(StateFigTypes::FIGURE_Stand);
				}
			}
		}
		else {
			if ((m_moveLimited - m_Vec2DPos.x) * m_direction.x * m_moveLimited >= 0) {
				GLfloat x = m_Vec2DPos.x + m_Speed * m_direction.x * deltaTime;
				Set2DPosition(x, m_Vec2DPos.y);
			}
			else {
				if (m_State == StateFigTypes::FIGURE_Inertia) {
					SetState(StateFigTypes::FIGURE_Stand);
				}
			}
		}
	}
}

GLint ActionPlayer::abs_value(GLint x) {
	return(x > 0 ? x : -x);
}



void Enemies::SetMoveControl(PlayerControls control) {
	m_currentControl = control;
	if (control == PlayerControls::CONTROL_Left) {
		m_direction.x = -1.0f;
		m_direction.y = 0.0f;
	}
	else if (control == PlayerControls::CONTROL_Right) {
		m_direction.x = 1.0f;
		m_direction.y = 0.0f;
	}
	else if (control == PlayerControls::CONTROL_Up) {
		m_direction.x = 0.0f;
		m_direction.y = -1.0f;
	}
	else if (control == PlayerControls::CONTROL_Down) {
		m_direction.x = 0.0f;
		m_direction.y = 1.0f;
	}
}
class ActionPlayer;
void ActionPlayer::Collision(GLint next_pos = 0) {
	m_direction.x = -m_direction.x;
	m_direction.y = -m_direction.y;
	m_moveLimited = next_pos;
	this->SetState(StateFigTypes::FIGURE_Inertia);
}
void ActionPlayer::Final() {

}

void ActionPlayer::Frozen() {}
void ActionPlayer::BeEaten() {}
void ActionPlayer::FallingDown() {}

void ActionPlayer::PickCake() {
	m_numCake++;
}

void ActionPlayer::Update(GLfloat deltaTime, bool is_allStand = false) {

	if (is_allStand == true&& m_currentControl != PlayerControls::CONTROL_Invalids) {
		this->SetState(StateFigTypes::FIGURE_Move);
		m_currentControl == PlayerControls::CONTROL_Invalids;
	}
	this->Move(deltaTime);
	this->Updated(deltaTime);
}

void ActionPlayer::DrawAction() {
	this->DrawCurrState();
}

