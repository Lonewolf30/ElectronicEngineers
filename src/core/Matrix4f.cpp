#include "Matrix4f.h"

Matrix4f Matrix4f::InitIdentity() {
	m[0][0] = 1; m[1][0] = 0; m[2][0] = 0; m[3][0] = 0;
	m[0][1] = 0; m[1][1] = 1; m[2][1] = 0; m[3][1] = 0;
	m[0][2] = 0; m[1][2] = 0; m[2][2] = 1; m[3][2] = 0;
	m[0][3] = 0; m[1][3] = 0; m[2][3] = 0; m[3][3] = 1;

	return *this;
}

Matrix4f Matrix4f::InitTranslation(Vector3d r)
{
	return InitTranslation(r.GetX(), r.GetY(), r.GetZ());
}

Matrix4f Matrix4f::InitTranslation(float x, float y, float z)
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = x;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = y;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = z;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	return *this;
}