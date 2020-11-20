#pragma once
#include"SpriteAnimation.h"
#include"ResourceManagers.h"
#include"ActionPlayer.h"


enum ItemTypes {
	ITEM_Stone,
	ITEM_Pond,
	ITEM_Tree,
	ITEM_Mine,
	ITEM_Cake,
	ITEM_Hole,
};

enum StateStaticTypes {
	STATIC_Invalids =0,
	STATIC_Silent,
	STATIC_Vibrate,
	STATIC_Destroyed
};
struct StateStaticAttribute {
	
	bool isLoop;
	std::shared_ptr<Texture> pTextureAnimation;
	StateStaticAttribute( bool _isLoop = true, std::shared_ptr<Texture> _pTextureAnimation = NULL) {
		

		isLoop = _isLoop;
		pTextureAnimation = _pTextureAnimation;
	}
};
class Figure;
class StaticObject :public SpriteAnimation {
private:
	GLint m_id;
	std::string m_Name;
protected:
	StateStaticTypes m_State;
	std::map<StateStaticTypes, const std::string> m_listState;
	std::map<const std::string, StateStaticAttribute> m_listAttrState;
	//std::shared_ptr<std::string, ;
	
	bool m_isChangeState;
	bool m_isLoop;
public:
	StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,GLint numFrames, GLfloat frameTime);
	//StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~StaticObject();
	GLint GetId();
	std::string GetName();
	void SetId(GLint id);
	void SetName(std::string name);
	StateStaticTypes GetCurrentState();

	void AddState(const std::string& str, StateStaticTypes statetype, StateStaticAttribute stateattr = StateStaticAttribute(true, NULL));
	void SetAnimation(StateStaticTypes state, bool isLoop, std::shared_ptr<Texture> textureAnimation);

	void SetState(StateStaticTypes state);
	bool IsChangeState();

	void DrawCurrState();
	void Updated(GLfloat deltaTime);
	void Init();
};
