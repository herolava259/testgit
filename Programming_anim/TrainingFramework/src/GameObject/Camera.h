#pragma once

#include "utilities.h" 


class Camera
{
	private:
	Vector3		m_VecCameraPos;
	Vector3		m_VecTargetPos;
	Vector3		m_VecUp;
	
	Matrix		m_MatView;
	Matrix		m_MatProjection;

	GLfloat		m_fSpeed;
	GLfloat		m_fNear;
	GLfloat		m_fFar;
	GLboolean	m_isChange;
	Matrix		GetMatView();
	Matrix		GetWorldMatrix();
	void 		MoveForward(GLfloat deltaTime);
	void 		MoveBackward(GLfloat deltaTime);
	void 		MoveLeft(GLfloat deltaTime);
	void 		MoveRight(GLfloat deltaTime);
	void 		RotationUp(GLfloat deltaTime);
	void 		RotationDown(GLfloat deltaTime);
	void 		RotationLeft(GLfloat deltaTime);
	void 		RotationRight(GLfloat deltaTime);
	Matrix		tempC;
	Matrix		tempWord;
public:
	Camera(void);
	~Camera(void);
	void		Init(Vector3 cameraPos,Vector3 targetPos,GLfloat fovY,GLfloat aspect,GLfloat fNear,GLfloat fFar,GLfloat fSpeed);
	Matrix		GetLookAtCamera();
	Vector3		GetLocation();
	void 		setTargetPosition(Vector4 vec);
	void		SetLocation(Vector3 pos);
	void		Move(GLbyte key, GLfloat deltaTime);
	GLfloat		GetNear();
	GLfloat		GetFar();

};

