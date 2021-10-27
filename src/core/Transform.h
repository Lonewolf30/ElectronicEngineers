#ifndef ELECTRONICENGINEERS_TRANSFORM_H
#define ELECTRONICENGINEERS_TRANSFORM_H

#include "Matrix4f.h"
#include "Quaternion.h"

class Transform {
private:
	Transform *parent;
	Matrix4<double> *parentMatrix;
	Vector3<double> *position;
	Vector3<double> *scale;
	Quaternion<double> *rotation;

	Matrix4<double> GetParentMatrix();

public:
	Transform();

	void Translate(Vector3<double> move);

	void Rotate(Vector3<double> axis, double angle);

	bool HasChanged();

	Matrix4<double> GetTransformation();

	Vector3<double> GetTransformedPos();

	Quaternion<double> GetTransformedRot();

	Transform *GetParent() const;

	Vector3<double> *GetPosition() const;

	Vector3<double> *GetScale() const;

	Quaternion<double> *GetRotation() const;

	void SetParent(Transform *parent);

	void SetScale(Vector3<double> *scale);

	void SetPosition(Vector3<double> *position);

	void SetRotation(Quaternion<double> *rotation);
};


#endif
