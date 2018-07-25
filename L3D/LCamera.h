#pragma once
#include "LMath.h"

class LCamera
{
public:
	const static float CAMERA_SPEED;

	LCamera(int _width, int _height, float _near, float _far, float _fov);
	~LCamera();

	float getNear() const;
	float getFar() const;
	float getFov() const;
	float getFovRad() const;
	float getAspectRatio() const;
	void setFov(float _fov);

	void rotate(float _x, float _y, float _z);

	matrix4 getCameraMatrix();

	vector3 getEye() const;
	void setEye(const vector3& eye);
	vector3 getLook() const;
	void setLook(const vector3& look);
	vector3 getPos() const;
	void setPos(const vector3& pos);
private:
	float fNear;
	float fFar;
	float fFov;
	float fAspectRatio;

	vector3 eye, look, pos;
};

