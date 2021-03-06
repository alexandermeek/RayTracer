#include "pch.h"
#include "Object3D.h"

#include <math.h>
#include <iostream>
using std::cout;

Object3D::Object3D() : kA(FloatRGB(0.3, 0.3, 0.3)), kD(FloatRGB(0.3, 0.3, 0.3)), kS(FloatRGB(0.3, 0.3, 0.3)), 
	lightType(UNIDIRECTIONAL) {}

Object3D::Object3D(const FloatRGB kA, const FloatRGB kD, const FloatRGB kS, const int lightType) 
	: kA(kA), kD(kD), kS(kS), lightType(lightType) {}

Object3D::~Object3D() {}

FloatRGB Object3D::getKA() const {
	return kA;
}
FloatRGB Object3D::getKD() const {
	return kD;
}
FloatRGB Object3D::getKS() const {
	return kS;
}

void Object3D::setKA(const FloatRGB kA) {
	this->kA = kA;
}

void Object3D::setKD(const FloatRGB kD) {
	this->kD = kD;
}

void Object3D::setKS(const FloatRGB kS) {
	this->kS = kS;
}

FloatRGB Object3D::getColourValue(const KDNode* kDNode, Vector3D point, Vector3D normal, std::vector<LightSource*>& lights, Ray ray, bool shadows) {
	normal = normal.unitVector();

	FloatRGB temp(0, 0, 0);
	for (LightSource* light : lights) {
		Vector3D lightDirection = (light->position - point).unitVector();

		float miss = 1;
		if (shadows) {
			Vector3D shifted_point = point + (normal * SHADOW_BIAS);
			float origin_offset;
			miss = light->calculateShadow(kDNode, shifted_point, origin_offset);
		}

		float nl = normal.dotProduct(lightDirection);
		if (lightType == BIDIRECTIONAL) { nl = abs(nl); }
		nl = nl < EPSILON ? 0.0f : nl;
		Vector3D reflVector = ((normal * 2 * nl) - lightDirection).unitVector();

		float vR = ray.direction.unitVector().dotProduct(reflVector) * -1;
		vR = vR < EPSILON ? 0.0f : vR;

		FloatRGB ambientLight = light->intensity * kA;
		FloatRGB diffuseLight = light->intensity * nl * kD * miss;
		FloatRGB specularLight = light->intensity * std::pow(vR, 10) * kS * miss;
		temp = temp + ambientLight + diffuseLight + specularLight;
	}

	FloatRGB colour(temp.r * 255.0f,
		temp.g * 255.0f, temp.b * 255.0f);

	return colour;
}

std::ostream& operator<<(std::ostream& os, const Object3D & rhs) {
	return os;
}
