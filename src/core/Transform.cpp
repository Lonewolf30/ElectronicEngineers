#include "Transform.h"

Transform::Transform() {
	parent = nullptr;
	parentMatrix = &(new Matrix4<double>())->InitIdentity();
	rotation = new Quaternion<double>(0, 0, 0, 1);
	scale = new Vector3<double>(1);
	position = new Vector3<double>(0);
}

void Transform::Translate(Vector3<double> move) {
	position = &(*position + move);
}

void Transform::Rotate(Vector3<double> axis, double angle) {
	rotation = &((Quaternion<double>(axis, angle) * *rotation).Normalized());
}

Vector3<double> *Transform::GetPosition() const {
	return position;
}

Vector3<double> *Transform::GetScale() const {
	return scale;
}

Quaternion<double> *Transform::GetRotation() const {
	return rotation;
}

Transform *Transform::GetParent() const {
	return parent;
}

void Transform::SetPosition(Vector3<double> *position) {
	Transform::position = position;
}

void Transform::SetScale(Vector3<double> *scale) {
	Transform::scale = scale;
}

void Transform::SetRotation(Quaternion<double> *rotation) {
	Transform::rotation = rotation;
}

void Transform::SetParent(Transform *parent) {
	Transform::parent = parent;
}

Quaternion<double> Transform::GetTransformedRot() {
	auto parentRotation = Quaternion<double>(0, 0, 0, 1);

	if (parent != nullptr)
		parentRotation = parent->GetTransformedRot();

	return parentRotation * *rotation;
}

Matrix4<double> Transform::GetParentMatrix() {
	if (parent != nullptr && parent->HasChanged())
		parentMatrix = &parent->GetTransformation();

	return *parentMatrix;
}

bool Transform::HasChanged() {
	return parent != nullptr && parent->HasChanged();
}

Matrix4<double> Transform::GetTransformation() {
	auto translationMatrix = Matrix4<double>().InitTranslation(position->CastTo<double>());
	auto rotationMatrix = rotation->ToRotationMatrix();
	auto scaleMatrix = Matrix4<double>().InitScale(scale->GetX(), scale->GetY(), scale->GetZ());

	return GetParentMatrix() * translationMatrix * rotationMatrix * scaleMatrix;
}

Vector3<double> Transform::GetTransformedPos() {
	return GetParentMatrix().Transform(*position);
}


