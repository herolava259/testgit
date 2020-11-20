#pragma once
#include"utilities.h"
#include"BaseObject.h"

class A : public BaseObject {

};
class MultiAnimationObj {
private:
	GLint m_Id;
	std::string m_Name;
protected:
	Vector3 m_Vec3Postion;
	Vector3 m_Vec3Scale;
	Vector3 m_Vec3Rotation;
	Vector4 m_Color;
	Matrix m_WorldMat;

	std::shared_ptr<Models> m_pModel;
	std::shared_ptr<Shaders> m_pShader;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Texture> m_pTexture;
public:
	MultiAnimationObj() {
		m_Id = 0;
		m_Name = "";
		m_Vec3Postion = Vector3(0.0, 0.0, 0.0);
		m_Vec3Scale = Vector3(0.0, 0.0, 0.0);
		m_Color = Vector4(0.0, 0.0, 0.0, 0.0);

	}
	void Set2DPostion(GLfloat x, GLfloat y, GLfloat z) {
		m_Vec3Postion.x = x;
		m_Vec3Postion.y = y;
		m_Vec3Postion.z = z;
	}
};