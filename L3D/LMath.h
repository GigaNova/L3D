#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>

struct vector2
{
	float x, y;
};

struct vector3
{
	float x, y, z;
};

struct vector4
{
	float x, y, z, a;
};

struct triangle
{
	vector3 points[3];
};

struct mesh
{
	std::vector<triangle> tris;
};

struct matrix4
{
	float m[4][4] = { 0 };
};

static void multiplyMatrixVector(vector3 &i, vector3 &o, matrix4 &m4)
{
	float w = 0.0f;
	o.x = i.x * m4.m[0][0] + i.y * m4.m[1][0] + i.z * m4.m[2][0] + m4.m[3][0];
	o.y = i.x * m4.m[0][1] + i.y * m4.m[1][1] + i.z * m4.m[2][1] + m4.m[3][1];
	o.z = i.x * m4.m[0][2] + i.y * m4.m[1][2] + i.z * m4.m[2][2] + m4.m[3][2];
	w = i.x * m4.m[0][3] + i.y * m4.m[1][3] + i.z * m4.m[2][3] + m4.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

static float cross(vector2 _vec1, vector2 _vec2)
{
	return _vec1.x * _vec2.y - _vec1.y * _vec2.x;
}

static vector3 cross(vector3 _vec1, vector3 _vec2)
{
	vector3 crossVec;
	crossVec.x = _vec1.y * _vec2.z - _vec1.z * _vec2.y;
	crossVec.y = _vec1.x * _vec2.z - _vec1.z * _vec2.x;
	crossVec.z = _vec1.x * _vec2.y - _vec1.y * _vec2.x;
	return crossVec;
}

static float length(vector3 _vec)
{
	return sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
}

static vector3 normalize(vector3 _vec) {
	vector3 vector;
	float l = length(_vec);

	if (l != 0) {
		vector.x = _vec.x / l;
		vector.y = _vec.y / l;
	}

	return vector;
}

static int sign(float val) {
	return (float(0) < val) - (val < float(0));
}

static float radian(float val)
{
	return val * 180.0 / M_PI;
}