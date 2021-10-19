#ifndef ELECTRONICENGINEERS_VECTOR3D_H
#define ELECTRONICENGINEERS_VECTOR3D_H

#include "../vec2/Vector2d.h"

#include <cmath>
#include <functional>

class Vector3d {
public:
	Vector3d();
	explicit Vector3d(double r);
	Vector3d(double x, double y, double z);

	double Length();
	double Max();
	double Dot(Vector3d r);

	Vector3d Cross(Vector3d r);
	Vector3d Normalized();
	Vector3d Abs();

	Vector3d Lerp(Vector3d r, float lerpFactor);

	Vector3d Rotate(Vector3d axis, float angle);

	Vector3d operator+(Vector3d r);
	Vector3d operator-(Vector3d r);
	Vector3d operator*(Vector3d r);
	Vector3d operator/(Vector3d r);

	Vector3d operator+(double r);
	Vector3d operator-(double r);
	Vector3d operator*(double r);
	Vector3d operator/(double r);

	Vector2d GetXY();
	Vector2d GetYZ();
	Vector2d GetZX();

	Vector2d GetYX();
	Vector2d GetZY();
	Vector2d GetXZ();

	bool Equals(Vector3d r);

	double GetX();
	double GetY();
	double GetZ();

	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);

private:
	double x, y, z;
};


#endif
