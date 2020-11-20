#include "Camera.h"



Camera::Camera()
{
	m_VecUp.x	= 0;
	m_VecUp.y	= 1;
	m_VecUp.z	= 0;
	m_MatView.SetZero();
	m_MatProjection.SetZero();
	m_isChange	= true;
}
Camera::~Camera()
{
}

void Camera::Init(Vector3 cameraPos,Vector3 targetPos,GLfloat fovY,GLfloat aspect,GLfloat fNear,GLfloat fFar,GLfloat fSpeed)
{
	m_VecCameraPos		= cameraPos;
	m_VecTargetPos		= targetPos;
	m_fNear				= fNear;
	m_fFar				= fFar;
	m_fSpeed			= fSpeed;
	m_MatProjection.SetPerspective(fovY,aspect,fNear,fFar);
}

GLfloat Camera::GetNear()
{
	return m_fNear;
}
GLfloat Camera::GetFar()
{
	return m_fFar;
}

Matrix Camera::GetMatView()
{
	if(m_isChange)
	{
		Vector3 zaxis		= (m_VecCameraPos-m_VecTargetPos).Normalize();
		Vector3 xaxis		= ( (m_VecUp.Cross(zaxis))).Normalize();
		Vector3 yaxis		= ( zaxis.Cross(xaxis)).Normalize();

		m_MatView.m[0][0]	= xaxis.x;
		m_MatView.m[1][0]	= xaxis.y;
		m_MatView.m[2][0]	= xaxis.z;
		m_MatView.m[3][0]	= -m_VecCameraPos.Dot(xaxis);
		m_MatView.m[0][1]	= yaxis.x;
		m_MatView.m[1][1]	= yaxis.y;
		m_MatView.m[2][1]	= yaxis.z;
		m_MatView.m[3][1]	= -m_VecCameraPos.Dot(yaxis);
		m_MatView.m[0][2]	= zaxis.x;
		m_MatView.m[1][2]	= zaxis.y;
		m_MatView.m[2][2]	= zaxis.z;
		m_MatView.m[3][2]	= -m_VecCameraPos.Dot(zaxis);
		m_MatView.m[0][3]	= 0;
		m_MatView.m[1][3]	= 0;
		m_MatView.m[2][3]	= 0;
		m_MatView.m[3][3]	= 1;

		m_isChange=false;
	}
	return m_MatView;
}

Matrix Camera::GetLookAtCamera()
{
	Matrix matrix = GetMatView();
	return matrix*m_MatProjection;
}

Vector3 Camera::GetLocation()
{
	return m_VecCameraPos;
}

Matrix Camera::GetWorldMatrix()
{

	Vector3 zaxis = (m_VecCameraPos-m_VecTargetPos).Normalize();
	Vector3 xaxis = ((m_VecUp.Cross(zaxis))).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	Matrix T;
	T.SetZero();
	T.m[0][0]	= 1;
	T.m[1][1]	= 1;
	T.m[2][2]	= 1;
	T.m[3][3]	= 1;
	T.m[3][0]	= m_VecCameraPos.x;
	T.m[3][1]	= m_VecCameraPos.y;
	T.m[3][2]	= m_VecCameraPos.z;

	Matrix R;
	R.m[0][0]	= xaxis.x;
	R.m[1][0]	= yaxis.x;
	R.m[2][0]	= zaxis.x;
	R.m[3][0]	= 0;
	R.m[0][1]	= xaxis.y;
	R.m[1][1]	= yaxis.y;
	R.m[2][1]	= zaxis.y;
	R.m[3][1]	= 0;
	R.m[0][2]	= xaxis.z;
	R.m[1][2]	= yaxis.z;
	R.m[2][2]	= zaxis.z;
	R.m[3][2]	= 0;
	R.m[0][3]	= 0;
	R.m[1][3]	= 0;
	R.m[2][3]	= 0;
	R.m[3][3]	= 1;

	return R*T;
}

void Camera::MoveForward(GLfloat deltaTime)
{
	m_isChange			=	true;
	Vector3 deltaMove	=	-(m_VecCameraPos-m_VecTargetPos).Normalize()*m_fSpeed;
	m_VecCameraPos		+=	deltaMove*deltaTime;
	m_VecTargetPos		+=	deltaMove*deltaTime;
}
void Camera::MoveBackward(GLfloat deltaTime)
{
	m_isChange			=	true;
	Vector3 deltaMove	=	-(m_VecCameraPos-m_VecTargetPos).Normalize()*m_fSpeed;
	m_VecCameraPos		-=	deltaMove*deltaTime;
	m_VecTargetPos		-=	deltaMove*deltaTime;
}
void Camera::MoveLeft(GLfloat deltaTime)
{
	m_isChange			=	true;
	Vector3 deltaMove	=	-(m_VecCameraPos-m_VecTargetPos).Normalize()*m_fSpeed;
	deltaMove			=	deltaMove.Cross(m_VecUp);
	m_VecCameraPos		-=	deltaMove*deltaTime;
	m_VecTargetPos		-=	deltaMove*deltaTime;
}

void Camera::MoveRight(GLfloat deltaTime)
{
	m_isChange			=	true;
	Vector3 deltaMove	=	-(m_VecCameraPos-m_VecTargetPos).Normalize()*m_fSpeed;
	deltaMove			=	deltaMove.Cross(m_VecUp);
	m_VecCameraPos		+=	deltaMove*deltaTime;
	m_VecTargetPos		+=	deltaMove*deltaTime;
}
void Camera::RotationUp(GLfloat deltaTime)
{
	m_isChange			=	true;
	Matrix matR;
	matR.SetRotationX(m_fSpeed*deltaTime);
	Vector4 localTarget =	Vector4( 0,0,-(m_VecCameraPos-m_VecTargetPos).Length(),1);
	localTarget			=	localTarget * matR;
	Vector4 WorldTarget	=	localTarget * GetWorldMatrix();
	setTargetPosition(WorldTarget);
}
void Camera::RotationDown(GLfloat deltaTime)
{
	m_isChange			=	true;
	Matrix matR;
	matR.SetRotationX(-m_fSpeed*deltaTime);
	Vector4 localTarget =	Vector4( 0,0,-(m_VecCameraPos-m_VecTargetPos).Length(),1);
	localTarget			=	localTarget * matR;
	Vector4 WorldTarget	=	localTarget*GetWorldMatrix();
	setTargetPosition(WorldTarget);
}
void Camera::RotationLeft(GLfloat deltaTime)
{
	m_isChange			=	true;
	Matrix matR;
	matR.SetRotationY(m_fSpeed*deltaTime);
	Vector4 localTarget =	Vector4(0,0, -(m_VecCameraPos-m_VecTargetPos).Length(),1);
	localTarget			=	localTarget * matR;
	Vector4 WorldTarget	=	localTarget*GetWorldMatrix();
	setTargetPosition(WorldTarget);
}
void Camera::RotationRight(GLfloat deltaTime)
{
	m_isChange			=	true;
	Matrix matR;
	matR.SetRotationY(-m_fSpeed*deltaTime);
	Vector4 localTarget = Vector4(0,0, -(m_VecCameraPos-m_VecTargetPos).Length(),1);
	localTarget			= localTarget * matR;
	Vector4 WorldTarget	= localTarget*GetWorldMatrix();
	setTargetPosition(WorldTarget);
}

void Camera::setTargetPosition(Vector4 vec)
{
	m_VecTargetPos.x	= vec.x;
	m_VecTargetPos.y	= vec.y;
	m_VecTargetPos.z	= vec.z;
}

void Camera::Move(GLbyte key, GLfloat deltaTime)
{
	switch (key)
	{
	case KEY_MOVE_FORWORD: 
		MoveForward(deltaTime) ; 
		break;
	case KEY_MOVE_BACKWORD: 
		MoveBackward(deltaTime) ; 
		break;
	case KEY_MOVE_LEFT: 
		MoveLeft(deltaTime);
		break;
	case KEY_MOVE_RIGHT:  
		MoveRight(deltaTime);
		break;
	case KEY_LEFT:  
		RotationLeft(deltaTime/2.0f);
		break;
	case KEY_RIGHT: 
		RotationRight(deltaTime/2.0f);
		break;
	case KEY_UP:  
		RotationUp(deltaTime/2.0f);
		break;
	case KEY_DOWN:  
		RotationDown(deltaTime/2.0f);
		break;
	}
}

void Camera::SetLocation(Vector3 pos)
{
	m_isChange=true;
	m_VecCameraPos = pos;
}
