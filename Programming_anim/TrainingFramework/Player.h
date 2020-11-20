#pragma once
#include"Sprite2D.h"
#include"SpriteAnimation.h"
#include<map>

struct StateAttribute {
	GLint numFrame;
	GLfloat frameTime;
	GLfloat speed;
	bool isLoop;
	std::shared_ptr<Texture> pTextureAnimation;
	StateAttribute(GLint _numFrame, GLfloat _frameTime, GLfloat _speed, bool _isLoop =true, std::shared_ptr<Texture> _pTextureAnimation = NULL) {
		numFrame = _numFrame;
		frameTime = _frameTime;
		speed = _speed;

		isLoop = _isLoop;
		pTextureAnimation = _pTextureAnimation;
	}
};
enum StateFigTypes {
	FIGURE_Invalids = 0,
	FIGURE_Move,
	FIGURE_Freeze,
	FIGURE_Dead,
	FIGURE_Success,
	FIGURE_Inertia,
	FIGURE_Stand
};
//class Sprite2D;
//class SpriteAnimation;


class Figure : public Sprite2D {
private:
	GLint m_Id;
	std::string m_Name;
protected:
	GLint m_numCake;
	StateFigTypes m_State;

	// Aimation
	std::map<StateFigTypes ,const std::string> m_listState;
	std::map<const std::string ,StateAttribute> m_listAttrState;
	std::shared_ptr<Shaders> m_pShaderAnim;
	//std::shared_ptr<std::string, ;
	GLint m_numFrames;
	GLint m_currentFrame;
	GLfloat m_frameTime;
	GLfloat m_currentTime;
	GLint m_Speed;
	bool m_isChangeState;
	bool m_isLoop;

public:
	Figure(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	Figure(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~Figure();

	GLint GetId();

	std::string GetName();
	void SetName(std::string str);

	GLint GetnumCake();
	void SetnumCake(GLint numCake);

	StateFigTypes GetCurrentState();

	void AddState(const std::string& str, StateFigTypes statetype, StateAttribute stateattr = StateAttribute(0, 0.0f, 0.0f, true, NULL));
	void SetFps(StateFigTypes state,GLint numFrame, GLfloat framTime, GLfloat speed,bool isLoop, std::shared_ptr<Texture> textureAnimation);

	void SetState(StateFigTypes state);
	bool IsChangeState();

	void DrawCurrState();
	void Updated(GLfloat deltaTime);
	void Init();

};