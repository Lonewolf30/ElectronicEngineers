#include "Vector3d.h"


Vector3d::Vector3d() {
	x = 0, y = 0, z = 0;
}


Vector3d::Vector3d(double r) {
	x = r, y = r, z = r;
}

Vector3d::Vector3d(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


double Vector3d::Length() {
	return sqrt(x * x + y * y + z * z);
}


Vector3d Vector3d::operator+(Vector3d r) {
	return {x + r.x, y + r.y, z + r.z};
}


Vector3d Vector3d::operator-(Vector3d r) {
	return {x - r.x, y - r.y, z - r.z};
}


Vector3d Vector3d::operator*(Vector3d r) {
	return {x * r.x, y * r.y, z * r.z};
}


Vector3d Vector3d::operator/(Vector3d r) {
	return {x / r.x, y / r.y, z / r.z};
}


Vector3d Vector3d::operator+(double r) {
	return {x + r, y + r, z + r};
}


Vector3d Vector3d::operator-(double r) {
	return {x - r, y - r, z - r};
}


Vector3d Vector3d::operator*(double r) {
	return {x * r, y * r, z * r};
}


Vector3d Vector3d::operator/(double r) {
	return {x / r, y / r, z / r};
}


Vector2d Vector3d::GetXY() {
	return {x, y};
}


Vector2d Vector3d::GetYZ() {
	return {y, z};
}


Vector2d Vector3d::GetZX() {
	return {z, x};
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
Vector2d Vector3d::GetYX() {
	return {y, x};
}
#pragma clang diagnostic pop


Vector2d Vector3d::GetZY() {
	return {z, y};
}


Vector2d Vector3d::GetXZ() {
	return {x, z};
}


bool Vector3d::Equals(Vector3d r) {
	return false;
}


double Vector3d::GetX() {
	return x;
}


double Vector3d::GetY() {
	return y;
}


double Vector3d::GetZ() {
	return z;
}


void Vector3d::SetX(double x) {
	this->x = x;
}


void Vector3d::SetY(double y) {
	this->y = y;
}


void Vector3d::SetZ(double z) {
	this->z = z;
}
