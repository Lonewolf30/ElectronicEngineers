#ifndef ELECTRONICENGINEERS_MATRIX4F_H
#define ELECTRONICENGINEERS_MATRIX4F_H

#include "vec3/Vector3d.h"

class Matrix4f {
public:

	Matrix4f InitIdentity();
	Matrix4f InitTranslation(Vector3d r);
	Matrix4f InitTranslation(float x, float y, float z);

private:
	float m[4][4] {};
};


#endif
