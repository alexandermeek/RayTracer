#include "pch.h"
#include "Object3D.h"

#include <iostream>
using std::cout;

Object3D::Object3D() {
	this->kA = FloatRGB(0.3, 0.3, 0.3);
	this->kD = FloatRGB(0.3, 0.3, 0.3);
	this->kS = FloatRGB(0.3, 0.3, 0.3);
	this->lightType = UNIDIRECTIONAL;
}

Object3D::Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS, int lightType) {
	this->kA = kA;
	this->kD = kD;
	this->kS = kS;
	this->lightType = lightType;
}

Object3D::~Object3D() {
}

FloatRGB Object3D::getKA() const {
	return kA;
}
FloatRGB Object3D::getKD() const {
	return kD;
}
FloatRGB Object3D::getKS() const {
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

bool Object3D::intersect(Ray ray, float& distance) {
	return false;
}

bool Object3D::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	return false;
}

Vector3D Object3D::getNormal(Vector3D point) {
	return Vector3D();
}

BoundingBox Object3D::getBoundingBox() const {
	return BoundingBox();
}

FloatRGB Object3D::getColourValue(KDNode* kDNode, Vector3D point, Vector3D normal, PointLight light, Ray ray, bool shadows) {
	normal = normal.unitVector();
	Vector3D lightDirection = (light.position - point).unitVector();

	float miss = 1;
	if (shadows) {
		Vector3D temp_point;
		Vector3D temp_normal;
		float distance(INT32_MAX);
		float origin_offset;
		Object3D* hitObject;
		Ray shadowRay(point, lightDirection);
		shadowRay.origin = point + (normal * SHADOW_BIAS);
		bool hit = kDNode->intersect(kDNode, shadowRay, &hitObject, temp_point, temp_normal, distance, origin_offset);

		if (hit) {
			miss = 0.1;
		}
	}

	float nl = normal.dotProduct(lightDirection);
	if (lightType == BIDIRECTIONAL) { nl = abs(nl); }
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

std::ostream& operator<<(std::ostream& os, const Object3D & rhs) {
	return os;
}
