#ifndef ELECTRONICENGINEERS_MATRIX4F_H
#define ELECTRONICENGINEERS_MATRIX4F_H

#include "Vector3.h"

template<class T>
class Matrix4 {
public:
	Matrix4 InitIdentity() {
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return *this;
	};

	Matrix4 InitTranslation(Vector3<T> r) {
		return InitTranslation(r.GetX(), r.GetY(), r.GetZ());
	};

	Matrix4 InitTranslation(T x, T y, T z) {
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = x;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = y;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = z;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return *this;
	};

	Matrix4 InitRotation(T x, T y, T z) {
		Matrix4 rx = new Matrix4();
		Matrix4 ry = new Matrix4();
		Matrix4 rz = new Matrix4();

		x = (float) toRadians(x);
		y = (float) toRadians(y);
		z = (float) toRadians(z);

		rz.m[0][0] = (float) cos(z);
		rz.m[0][1] = -(float) sin(z);
		rz.m[0][2] = 0;
		rz.m[0][3] = 0;
		rz.m[1][0] = (float) sin(z);
		rz.m[1][1] = (float) cos(z);
		rz.m[1][2] = 0;
		rz.m[1][3] = 0;
		rz.m[2][0] = 0;
		rz.m[2][1] = 0;
		rz.m[2][2] = 1;
		rz.m[2][3] = 0;
		rz.m[3][0] = 0;
		rz.m[3][1] = 0;
		rz.m[3][2] = 0;
		rz.m[3][3] = 1;

		rx.m[0][0] = 1;
		rx.m[0][1] = 0;
		rx.m[0][2] = 0;
		rx.m[0][3] = 0;
		rx.m[1][0] = 0;
		rx.m[1][1] = (float) cos(x);
		rx.m[1][2] = -(float) sin(x);
		rx.m[1][3] = 0;
		rx.m[2][0] = 0;
		rx.m[2][1] = (float) sin(x);
		rx.m[2][2] = (float) cos(x);
		rx.m[2][3] = 0;
		rx.m[3][0] = 0;
		rx.m[3][1] = 0;
		rx.m[3][2] = 0;
		rx.m[3][3] = 1;

		ry.m[0][0] = (float) cos(y);
		ry.m[0][1] = 0;
		ry.m[0][2] = -(float) sin(y);
		ry.m[0][3] = 0;
		ry.m[1][0] = 0;
		ry.m[1][1] = 1;
		ry.m[1][2] = 0;
		ry.m[1][3] = 0;
		ry.m[2][0] = (float) sin(y);
		ry.m[2][1] = 0;
		ry.m[2][2] = (float) cos(y);
		ry.m[2][3] = 0;
		ry.m[3][0] = 0;
		ry.m[3][1] = 0;
		ry.m[3][2] = 0;
		ry.m[3][3] = 1;

		m = (rz * (ry * rx)).GetM();

		return *this;
	}

	Matrix4 InitScale(T x, T y, T z) {
		m[0][0] = x;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = y;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = z;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return *this;
	}

	Matrix4 InitPerspective(float fov, float aspectRatio, float zNear, float zFar) {
		auto tanHalfFOV = (float) tan(fov / 2);
		float zRange = zNear - zFar;

		m[0][0] = 1.0f / (tanHalfFOV * aspectRatio);
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1.0f / tanHalfFOV;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = (-zNear - zFar) / zRange;
		m[2][3] = 2 * zFar * zNear / zRange;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 1;
		m[3][3] = 0;


		return *this;
	}

	Matrix4 InitOrthographic(float left, float right, float bottom, float top, float near, float far) {
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;

		m[0][0] = 2 / width;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = -(right + left) / width;
		m[1][0] = 0;
		m[1][1] = 2 / height;
		m[1][2] = 0;
		m[1][3] = -(top + bottom) / height;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = -2 / depth;
		m[2][3] = -(far + near) / depth;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return *this;
	}

	Matrix4 InitRotation(Vector3<T> forward, Vector3<T> up) {
		Vector3 f = forward.Normalized();

		Vector3 r = up.Normalized();
		r = r.Cross(f);

		Vector3 u = f.Cross(r);

		return InitRotation(f, u, r);
	}

	Matrix4 InitRotation(Vector3<T> forward, Vector3<T> up, Vector3<T> right) {
		m[0][0] = right.GetX();
		m[0][1] = right.GetY();
		m[0][2] = right.GetZ();
		m[0][3] = 0;
		m[1][0] = up.GetX();
		m[1][1] = up.GetY();
		m[1][2] = up.GetZ();
		m[1][3] = 0;
		m[2][0] = forward.GetX();
		m[2][1] = forward.GetY();
		m[2][2] = forward.GetZ();
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;

		return *this;
	}

	Vector3<T> Transform(Vector3<T> r) {
		return Vector3<T>(m[0][0] * r.GetX() + m[0][1] * r.GetY() + m[0][2] * r.GetZ() + m[0][3],
						  m[1][0] * r.GetX() + m[1][1] * r.GetY() + m[1][2] * r.GetZ() + m[1][3],
						  m[2][0] * r.GetX() + m[2][1] * r.GetY() + m[2][2] * r.GetZ() + m[2][3]);
	}

	Matrix4 operator*(Matrix4<T> r) {
		auto res = Matrix4<T>();

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				res.Set(i, j, m[i][0] * r.Get(0, j) +
							  m[i][1] * r.Get(1, j) +
							  m[i][2] * r.Get(2, j) +
							  m[i][3] * r.Get(3, j));
			}
		}

		return res;
	}

	T **GetM() { return m; }

	T Get(int x, int y) { return m[x][y]; }

	void SetM(T **m) { this->m = m; }

	void Set(int x, int y, T value) { m[x][y] = value; }

private:
	T m[4][4];
};


#endif
