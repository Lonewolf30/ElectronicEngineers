#include "Vector2d.h"

Vector2d::Vector2d(double r) {
	x = r,y = r;
}

Vector2d::Vector2d(double _x, double _y) {
	x = _x;
	y = _y;
}

double Vector2d::Length() {
	return static_cast<double>(sqrt(pow(x, 2) + pow(y, 2)));
}

double Vector2d::Dot(Vector2d r) {
	return static_cast<double>(x * r.x + y * r.y);
}

double Vector2d::Cross(Vector2d r) {
	return static_cast<double>(x * r.y - y * r.x);
}

double Vector2d::Ratio() {
	return static_cast<double>(x / y);
}

Vector2d Vector2d::Lerp(Vector2d dest, double factor) {
	return ((dest - *this) * factor) + *this;
}

Vector2d Vector2d::Rotate(double radians) {
	const double cosine = cos(radians);
	const double sine = sin(radians);

	return Vector2d{ (x * cosine - y * sine), (x * sine + y * cosine) };
}

Vector2d Vector2d::Normalised() {
	double length = Length();
	return {x/length, y/length};
}


Vector2d Vector2d::Abs() {
	return Vector2d(abs(x), abs(y));
}


void Vector2d::SetX(double _x) {
	x = _x;
}


void Vector2d::SetY(double _y) {
	y = _y;
}


double Vector2d::GetX() {
	return x;
}


double Vector2d::GetY() {
	return y;
}


bool Vector2d::equals(Vector2d vec2) {
	return vec2.x == x && vec2.y == y;
}


Vector2d Vector2d::operator+(Vector2d vec2) {
	return {x+vec2.x, y+vec2.y};
}


Vector2d Vector2d::operator-(Vector2d vec2) {
	return {x-vec2.x, y-vec2.y};
}

Vector2d Vector2d::operator*(Vector2d vec2) {
	return {x*vec2.x, y*vec2.y};
}


Vector2d Vector2d::operator/(Vector2d vec2) {
	return {x/vec2.x, y/vec2.y};
}


Vector2d Vector2d::operator+(double r) {
	return {x+r,y+r};
}


Vector2d Vector2d::operator-(double r) {
	return {x-r,y-r};
}


Vector2d Vector2d::operator*(double r) {
	return {x*r,y*r};
}


Vector2d Vector2d::operator/(double r) {
	return {x/r,y/r};
}