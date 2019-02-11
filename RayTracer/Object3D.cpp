#include "pch.h"
#include "Object3D.h"

#include <iostream>
using std::cout;

Object3D::Object3D() {
	this->kA = FloatRGB(1, 1, 1);
	this->kD = FloatRGB(1, 1, 1);
	this->kS = FloatRGB(1, 1, 1);
	this->useBidirectionalLight = false;
}

Object3D::Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS, bool useBidirectionalLight) {
	this->kA = kA;
	this->kD = kD;
	this->kS = kS;
	this->useBidirectionalLight = useBidirectionalLight;
}

Object3D::~Object3D() {
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

void Object3D::setKA(FloatRGB kA) {
	this->kA = kA;
}

void Object3D::setKD(FloatRGB kD) {
	this->kD = kD;
}

void Object3D::setKS(FloatRGB kS) {
	this->kS = kS;
}

bool Object3D::intersect(Ray ray) {
	return false;
}

bool Object3D::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	return false;
}

bool Object3D::intersect(Ray ray, float& distance) {
	return false;
}

Vector3D Object3D::getNormal(Vector3D point) {
	return Vector3D();
}

FloatRGB Object3D::getColourValue(std::vector<Object3D*>& objects, Vector3D point, Vector3D normal, PointLight light, Ray ray) {
	normal = normal.unitVector();
	Vector3D lightDirection = (light.position - point).unitVector();

	float miss = 1;
	Ray shadowRay;
	for (Object3D* obj : objects) {
		if (!(this == obj)) {
			shadowRay = Ray (point, lightDirection);
			if (obj->intersect(shadowRay)) {
				miss = 0.1;
			}
		}
	}

	float nl = normal.dotProduct(lightDirection);
	if (useBidirectionalLight) { nl = abs(nl); }
	nl = nl < EPSILON ? 0.0f : nl;
	Vector3D reflVector = ((normal * 2 * nl) - lightDirection).unitVector();

	float vR = ray.direction.unitVector().dotProduct(reflVector) * -1;
	vR = vR < EPSILON ? 0.0f : vR;

	FloatRGB ambientLight = light.intensity * kA;
	FloatRGB diffuseLight = light.intensity * nl * kD * miss;
	FloatRGB specularLight = light.intensity * pow(vR, 10) * kS * miss;
	FloatRGB temp = ambientLight + diffuseLight + specularLight;

	FloatRGB colour(temp.r * 255.0f,
		temp.g * 255.0f, temp.b * 255.0f);

	return colour;
}

std::string Object3D::toString()
{
	return std::string();
}
