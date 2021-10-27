#ifndef ELECTRONICENGINEERS_VECTOR2_H
#define ELECTRONICENGINEERS_VECTOR2_H

#include <cmath>

template<class T>
class Vector2 {
public:
	explicit Vector2(T r) {
		x = r, y = r;
	};

	Vector2(T _x, T _y) {
		x = _x;
		y = _y;
	};

	T Length() { return static_cast<T>(sqrt(pow(x, 2) + pow(y, 2))); };

	T Dot(Vector2 r) { return static_cast<T>(x * r.x + y * r.y); };

	T Cross(Vector2 r) { return static_cast<T>(x * r.y - y * r.x); };

	T Ratio() { return static_cast<T>(x / y); };

	Vector2 Lerp(Vector2 dest, double factor) { return ((dest - *this) * factor) + *this; }

	Vector2 Rotate(double radians) {
		const double cosine = cos(radians);
		const double sine = sin(radians);

		return Vector2{(x * cosine - y * sine), (x * sine + y * cosine)};
	};

	Vector2 operator+(Vector2 vec2) { return {x + vec2.x, y + vec2.y}; };

	Vector2 operator-(Vector2 vec2) { return {x - vec2.x, y - vec2.y}; };

	Vector2 operator*(Vector2 vec2) { return {x * vec2.x, y * vec2.y}; };

	Vector2 operator/(Vector2 vec2) { return {x / vec2.x, y / vec2.y}; };

	Vector2 operator+(T r) { return {x + r, y + r}; };

	Vector2 operator-(T r) { return {x - r, y - r}; };

	Vector2 operator*(T r) { return {x * r, y * r}; };

	Vector2 operator/(T r) { return {x / r, y / r}; };

	Vector2 Normalised() {
		double length = Length();
		return {x / length, y / length};
	};

	Vector2 Abs() { return Vector2(abs(x), abs(y)); };

	void SetX(T _x) { this->x = x; };

	void SetY(T _y) { this->y = y; };

	T GetX() { return x; };

	T GetY() { return y; };

	bool equals(Vector2 vec2) { return vec2.x == x && vec2.y == y; };
private:
	T x, y;
};

#endif
