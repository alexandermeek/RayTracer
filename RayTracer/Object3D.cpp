#include "pch.h"
#include "Object3D.h"

Object3D::Object3D(ColourRGB colour, float kA, float kD, float kS)
{
	this->colour = colour;
	this->kA = kA;
	this->kD = kD;
	this->kS = kS;
}

Object3D::~Object3D()
{
}

ColourRGB Object3D::getColour() {
	return colour;
}
float Object3D::getKA() {
	return kA;
}
float Object3D::getKD() {
	return kD;
}
float Object3D::getKS() {
	return kS;
}

bool Object3D::intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D & point)
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
