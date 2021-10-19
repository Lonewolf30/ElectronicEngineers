#ifndef ELECTRONICENGINEERS_VECTOR2D_H
#define ELECTRONICENGINEERS_VECTOR2D_H

#include <cmath>
#include <functional>

class Vector2d {
public:
	explicit Vector2d(double r);

	Vector2d(double _x, double _y);
	
	double Length();

	double Dot(Vector2d r);

	double Cross(Vector2d r);

	double Ratio();

	Vector2d Lerp(Vector2d dest, double factor);

	Vector2d Rotate(double radians);

	Vector2d operator+(Vector2d vec2);

	Vector2d operator-(Vector2d vec2);

	Vector2d operator*(Vector2d vec2);

	Vector2d operator/(Vector2d vec2);

	Vector2d operator+(double r);

	Vector2d operator-(double r);

	Vector2d operator*(double r);

	Vector2d operator/(double r);

	Vector2d Normalised();

	Vector2d Abs();

	void SetX(double _x);

	void SetY(double _y);

	double GetX();

	double GetY();

	bool equals(Vector2d vec2);

private:
	double x, y;
};

#endif
