#include "LCamera.h"
#include <math.h>

float const LCamera::CAMERA_SPEED = 0.05f;

LCamera::LCamera(int _width, int _height, float _near, float _far, float _fov)
{
	fNear = _near;
	fFar = _far;
	fFov = _fov;
	fAspectRatio = (float)_width / (float)_height;

	eye =  { 1, 0, 0 };
	look = { 0, 1, 0 };
	pos =  { 0, 0, 1 };
}

LCamera::~LCamera()
{
}

float LCamera::getNear() const
{
	return fNear;
}

float LCamera::getFar() const
{
	return fFar;
}

float LCamera::getFov() const
{
	return fFov;
}

float LCamera::getFovRad() const
{
	float fovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
	return fovRad;
}

float LCamera::getAspectRatio() const
{
	return fAspectRatio;
}

void LCamera::setFov(float _fov)
{
	fFov = _fov;
}

void LCamera::rotate(float _x, float _y, float _z)
{
	eye.x += cosf(_x * CAMERA_SPEED);
	eye.y += sinf(_y * CAMERA_SPEED);

	look.x += -cosf(_x * CAMERA_SPEED);
	look.y += sinf(_y * CAMERA_SPEED);
}

matrix4 LCamera::getCameraMatrix()
{
	matrix4 camMatrix;

	camMatrix.m[0][0] = eye.x;
	camMatrix.m[0][1] = eye.y;
	camMatrix.m[0][2] = eye.z;
	camMatrix.m[0][3] = 0.0f;

	camMatrix.m[1][0] = look.x;
	camMatrix.m[1][1] = look.y;
	camMatrix.m[1][2] = look.z;
	camMatrix.m[1][3] = 0.0f;

	camMatrix.m[2][0] = pos.x;
	camMatrix.m[2][1] = pos.y;
	camMatrix.m[2][2] = 0.0f;
	camMatrix.m[2][3] = pos.z;

	camMatrix.m[3][0] = 0.0f;
	camMatrix.m[3][1] = 0.0f;
	camMatrix.m[3][2] = 0.0f;
	camMatrix.m[3][3] = 1.0f;

	return camMatrix;
}

vector3 LCamera::getEye() const
{
	return eye;
}

void LCamera::setEye(const vector3& eye)
{
	this->eye = eye;
}

vector3 LCamera::getLook() const
{
	return look;
}

void LCamera::setLook(const vector3& look)
{
	this->look = look;
}

vector3 LCamera::getPos() const
{
	return pos;
}

void LCamera::setPos(const vector3& pos)
{
	this->pos = pos;
}

