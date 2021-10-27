#include <cmath>
#include <functional>

#ifndef ELECTRONICENGINEERS_Vector3_H
#define ELECTRONICENGINEERS_Vector3_H

#include "Vector2.h"

template<class T>
class Vector3 {
public:
	Vector3() { x = 0, y = 0, z = 0; };

	explicit Vector3(T r) { x = r, y = r, z = r; };

	Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	double Length() { return sqrt(x * x + y * y + z * z); };

	double Dot(Vector3 r) { return x * r.x + y * r.y + z * r.z; };

	Vector3 Cross(Vector3 r) {
		T x_ = y * r.GetZ() - z * r.GetY();
		T y_ = z * r.GetX() - x * r.GetZ();
		T z_ = x * r.GetY() - y * r.GetX();

		return Vector3<T>(x_, y_, z_);
	};

	Vector3 Normalized() {
		T length = Length();
		return Vector3<T>(x / length, y / length, z / length);
	};

	Vector3 Abs() { return Vector3<T>(static_cast<T>(abs(x)), static_cast<T>(abs(y)), static_cast<T>(abs(z))); };

	Vector3 Lerp(Vector3 dest, float lerpFactor){return (dest - *this) * lerpFactor + *this;};

	Vector3 Rotate(Vector3 axis, float angle) {
		auto sinAngle = sin(-angle);
		auto cosAngle = cos(-angle);

		return this->Cross(axis * sinAngle).Add(*this * cosAngle).Add(axis * this->Dot(axis * (1 - cosAngle)));
	};

	Vector3 operator+(Vector3 r) { return {x + r.x, y + r.y, z + r.z}; };

	Vector3 operator-(Vector3 r) { return {x - r.x, y - r.y, z - r.z}; };

	Vector3 operator*(Vector3 r) { return {x * r.x, y * r.y, z * r.z}; };

	Vector3 operator/(Vector3 r) { return {x / r.x, y / r.y, z / r.z}; };

	Vector3 operator+(double r) { return {x + r, y + r, z + r}; };

	Vector3 operator-(double r) { return {x - r, y - r, z - r}; };

	Vector3 operator*(double r) { return {x * r, y * r, z * r}; };

	Vector3 operator/(double r) { return {x / r, y / r, z / r}; };

	Vector2<T> GetXY() { return new Vector2<T>(x, y); };

	Vector2<T> GetYZ() { return new Vector2<T>(y, z); };

	Vector2<T> GetZX() { return new Vector2<T>(z, x); };

	Vector2<T> GetYX() { return new Vector2<T>(y, x); };

	Vector2<T> GetZY() { return new Vector2<T>(z, y); };

	Vector2<T> GetXZ() { return new Vector2<T>(x, z); };

	bool Equals(Vector3 r) { return false; };

	T GetX() { return x; };

	T GetY() { return y; };

	T GetZ() { return z; };

	void SetX(T x) { this->x = x; };

	void SetY(T y) { this->y = y; };

	void SetZ(T z) { this->z = z; };

	template<class Y>
	Vector3<Y> CastTo() {
		return Vector3<Y>(x, y, z);
	}

private:
	T x, y, z;
};


#endif
