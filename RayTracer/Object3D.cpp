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

bool Object3D::intersect(Vector3D rayOrigin, Vector3D directionVector) {
	return false;
}

bool Object3D::intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, 
	Vector3D& point, float& distance, PointLight& light, FloatRGB& colour)
{
	return false;
}

Vector3D Object3D::getNormal(Vector3D point)
{
	return Vector3D();
}

FloatRGB Object3D::getColourValue(std::vector<Object3D*>& objects, Vector3D point, Vector3D normal, PointLight& light, Vector3D rayOrigin) {
	normal = normal.unitVector();
	Vector3D lightDirection = (point - light.getPosition()).unitVector();
	Vector3D viewDirection = (rayOrigin - point).unitVector();

	float hit = 1;
	for (Object3D* obj : objects) {
		if (obj->intersect(point, light.getPosition() - point)) {
			hit = 0;
		}
	}

	float nl = normal.dotProduct(lightDirection);
	nl = nl < 0 ? 0.0f : nl;
	Vector3D reflVector = ((normal * 2 * nl) - lightDirection).unitVector();

	float vR = viewDirection.dotProduct(reflVector) * -1;
	vR = vR < 0 ? 0.0f : vR;

	FloatRGB ambientLight = light.getIntensity() * kA;
	FloatRGB diffuseLight = light.getIntensity() * normal.dotProduct(lightDirection) * kD * hit;
	FloatRGB specularLight = light.getIntensity() * std::pow(vR, 9) * hit;
	FloatRGB temp = ambientLight + diffuseLight + specularLight;

	temp.r = temp.r > 1 ? 1 : temp.r;
	temp.g = temp.g > 1 ? 1 : temp.g;
	temp.b = temp.b > 1 ? 1 : temp.b;

	FloatRGB colour(temp.r * 255,
		temp.g * 255, temp.b * 255);

	return colour;
}

FloatRGB Object3D::getColourValue(std::vector<Object3D*>& objects, Vector3D point, PointLight& light, Vector3D rayOrigin) {
	return FloatRGB();
}

std::string Object3D::toString()
{
	return std::string();
}
