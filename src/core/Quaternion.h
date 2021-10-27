#include <cmath>

#ifndef ELECTRONICENGINEERS_QUATERNION_H
#define ELECTRONICENGINEERS_QUATERNION_H

using namespace std;

template<class T>
class Quaternion {
public:
	Quaternion(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion(Vector3<T> axis, double radians) {
		auto sinHalfAngle = sin(radians / 2);
		auto cosHalfAngle = cos(radians / 2);

		this->x = axis.GetX() * sinHalfAngle;
		this->y = axis.GetY() * sinHalfAngle;
		this->z = axis.GetZ() * sinHalfAngle;
		this->w = cosHalfAngle;
	}

	T Length() { return static_cast<T>(sqrt(x * x + y * y + z * z + w * w)); };

	Quaternion Normalized() {
		T length = Length();
		return Quaternion<T>(x / length, y / length, z / length, w / length);
	};

	Quaternion Conjugate() { return new Quaternion<T>(-x, -y, -z, w); };

	Quaternion operator+(T r) { return Quaternion<T>(x + r, y + r, z + r, w + r); };

	Quaternion operator-(T r) { return Quaternion<T>(x - r, y - r, z - r, w - r); };

	Quaternion operator*(T r) { return Quaternion<T>(x * r, y * r, z * r, w * r); };

	Quaternion operator/(T r) { return Quaternion<T>(x / r, y / r, z / r, w / r); };

	Quaternion<T> operator*(Quaternion<T> r) {
		float w_ = w * r.GetW() - x * r.GetX() - y * r.GetY() - z * r.GetZ();
		float x_ = x * r.GetW() + w * r.GetX() + y * r.GetZ() - z * r.GetY();
		float y_ = y * r.GetW() + w * r.GetY() + z * r.GetX() - x * r.GetZ();
		float z_ = z * r.GetW() + w * r.GetZ() + x * r.GetY() - y * r.GetX();

		return Quaternion<T>(x_, y_, z_, w_);
	};

	Quaternion operator*(Vector3<T> r) {
		T w_ = -x * r.GetX() - y * r.GetY() - z * r.GetZ();
		T x_ = w * r.GetX() + y * r.GetZ() - z * r.GetY();
		T y_ = w * r.GetY() + z * r.GetX() - x * r.GetZ();
		T z_ = w * r.GetZ() + x * r.GetY() - y * r.GetX();

		return Quaternion<T>(x_, y_, z_, w_);
	}

	Matrix4<T> ToRotationMatrix() {
		Vector3<T> forward = Vector3<T>(2.0f * (x * z - w * y), 2.0f * (y * z + w * x),
											1.0f - 2.0f * (x * x + y * y));
		Vector3<T> up = Vector3<T>(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
		Vector3<T> right = Vector3<T>(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z),
										  2.0f * (x * z + w * y));

		return (new Matrix4<T>())->InitRotation(forward, up, right);
	};

	T Dot(Quaternion r) { return x * r.GetX() + y * r.GetY() + z * r.GetZ() + w * r.GetW(); };

	Quaternion NLerp(Quaternion dest, float lerpFactor, bool shortest) {
		Quaternion correctedDest = dest;

		if (shortest && this->Dot(dest) < 0)
			correctedDest = new Quaternion(-dest.GetX(), -dest.GetY(), -dest.GetZ(), -dest.GetW());

		return correctedDest.Sub(this).Mul(lerpFactor).Add(this).Normalized();
	}

	Quaternion SLerp(Quaternion dest, float lerpFactor, bool shortest) {
		const float EPSILON = 1e3f;

		float cos = this->Dot(dest);
		Quaternion correctedDest = dest;

		if (shortest && cos < 0) {
			cos = -cos;
			correctedDest = new Quaternion(-dest.GetX(), -dest.GetY(), -dest.GetZ(), -dest.GetW());
		}

		if (abs(cos) >= 1 - EPSILON)
			return NLerp(correctedDest, lerpFactor, false);

		auto sinus = sqrt(1.0f - cos * cos);
		auto angle = atan2(sinus, cos);
		auto invSin = 1.0f / sinus;

		float srcFactor = sin((1.0f - lerpFactor) * angle) * invSin;
		float destFactor = sin((lerpFactor) * angle) * invSin;

		return this->Mul(srcFactor).Add(correctedDest.Mul(destFactor));
	}

	//From Ken Shoemake's "Quaternion Calculus and Fast Animation" article
	explicit Quaternion(Matrix4<T> rot) {
		T trace = rot.Get(0, 0) + rot.Get(1, 1) + rot.Get(2, 2);

		if (trace > 0) {
			float s = 0.5f / (float) sqrt(trace + 1.0f);
			w = 0.25f / s;
			x = (rot.Get(1, 2) - rot.Get(2, 1)) * s;
			y = (rot.Get(2, 0) - rot.Get(0, 2)) * s;
			z = (rot.Get(0, 1) - rot.Get(1, 0)) * s;
		} else {
			if (rot.Get(0, 0) > rot.Get(1, 1) && rot.Get(0, 0) > rot.Get(2, 2)) {
				float s = 2.0f * (float) sqrt(1.0f + rot.Get(0, 0) - rot.Get(1, 1) - rot.Get(2, 2));
				w = (rot.Get(1, 2) - rot.Get(2, 1)) / s;
				x = 0.25f * s;
				y = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
				z = (rot.Get(2, 0) + rot.Get(0, 2)) / s;
			} else if (rot.Get(1, 1) > rot.Get(2, 2)) {
				float s = 2.0f * (float) sqrt(1.0f + rot.Get(1, 1) - rot.Get(0, 0) - rot.Get(2, 2));
				w = (rot.Get(2, 0) - rot.Get(0, 2)) / s;
				x = (rot.Get(1, 0) + rot.Get(0, 1)) / s;
				y = 0.25f * s;
				z = (rot.Get(2, 1) + rot.Get(1, 2)) / s;
			} else {
				float s = 2.0f * (float) sqrt(1.0f + rot.Get(2, 2) - rot.Get(0, 0) - rot.Get(1, 1));
				w = (rot.Get(0, 1) - rot.Get(1, 0)) / s;
				x = (rot.Get(2, 0) + rot.Get(0, 2)) / s;
				y = (rot.Get(1, 2) + rot.Get(2, 1)) / s;
				z = 0.25f * s;
			}
		}

		auto length = sqrt(x * x + y * y + z * z + w * w);
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	Vector3<T> RotateVector3(Vector3<T> vec) {
		Quaternion conjugate = Conjugate();
		Quaternion temp = *this * vec * conjugate;
		return Vector3<T>(temp.x, temp.y, temp.z);
	}

	Vector3<T> GetForward() { return RotateVector3(Vector3<T>(0, 0, 1)); }

	Vector3<T> GetBack() { return RotateVector3(Vector3<T>(0, 0, -1)); }

	Vector3<T> GetUp() { return RotateVector3(Vector3<T>(0, 1, 0)); }

	Vector3<T> GetDown() { return RotateVector3(Vector3<T>(0, -1, 0)); }

	Vector3<T> GetRight() { return RotateVector3(Vector3<T>(1, 0, 0)); }

	Vector3<T> GetLeft() { return RotateVector3(Vector3<T>(-1, 0, 0)); }

	void setX(T x) { this->x = x; }

	void setY(T y) { this->y = y; }

	void setZ(T z) { this->z = z; }

	void setW(T w) { this->w = w; }

	T GetX() const { return x; }

	T GetY() const { return y; }

	T GetZ() const { return z; }

	T GetW() const { return w; }

private:
	T x, y, z, w;
};


#endif
