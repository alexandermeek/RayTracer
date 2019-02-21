#include "pch.h"
#include "Box.h"

using std::endl;

Box::Box() 
	: Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), UNIDIRECTIONAL) {
}

Box::Box(const Box &box) 
	: Object3D(box) {
	this->vmin = box.vmin;
	this->vmax = box.vmax;
}

Box::Box(Vector3D vmin, Vector3D vmax) 
	: Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), UNIDIRECTIONAL) {
	this->vmin = vmin;
	this->vmax = vmax;
}

Box::Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS, UNIDIRECTIONAL) {
	this->vmin = vmin;
	this->vmax = vmax;
}

Box::~Box() {}

bool Box::intersect(const Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!BoundingBox::intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

Vector3D Box::getNormal(Vector3D point) {
	Vector3D centre = getCentre();
	Vector3D normal = (point - centre);
	Vector3D divisor = (vmin - vmax) / 2.0f;
	divisor.x = abs(divisor.x);
	divisor.y = abs(divisor.y);
	divisor.z = abs(divisor.z);

	const float bias = 1.000010f;

	normal = normal / divisor * bias;
	normal.x = (int) normal.x;
	normal.y = (int) normal.y;
	normal.z = (int) normal.z;

	return normal.unitVector();
}

BoundingBox Box::getBoundingBox() const {
	return BoundingBox(vmin, vmax);
}

Box Box::operator=(const Box &box) {
	return Box(box.vmin, box.vmax, box.getKA(), box.getKD(), box.getKS());
}

std::string Box::toString() const {
	return BoundingBox::toString();
}
