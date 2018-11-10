#include "pch.h"
#include "Object3D.h"

Object3D::Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS)
{
	this->kA = kA;
	this->kD = kD;
	this->kS = kS;
}

Object3D::~Object3D()
{
}

FloatRGB Object3D::getKA() {
	return kA;
}
FloatRGB Object3D::getKD() {
	return kD;
}
FloatRGB Object3D::getKS() {
	return kS;
}

bool Object3D::intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance)
{
	return false;
}

Vector3D Object3D::getNormal(Vector3D point)
{
	return Vector3D();
}

std::string Object3D::toString()
{
	return std::string();
}
