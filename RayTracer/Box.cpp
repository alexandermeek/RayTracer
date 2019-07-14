#include "pch.h"
#include "Box.h"

#include <math.h>

using std::endl;

Box::Box() 
	: Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), UNIDIRECTIONAL) {
}

Box::Box(const Box &box) 
	: BoundingBox(box), Object3D(box) {}

Box::Box(Vector3D vmin, Vector3D vmax) 
	: BoundingBox(vmin, vmax),
	  Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), UNIDIRECTIONAL) {}

Box::Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: BoundingBox(vmin, vmax), Object3D(kA, kD, kS, UNIDIRECTIONAL) {}

bool Box::intersect(const Ray ray, float& distance) const {
	return BoundingBox::intersect(ray, distance);
}

bool Box::intersect(const Ray ray, Vector3D& point, Vector3D& normal, float& distance) const {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

Vector3D Box::getNormal(Vector3D point) const {
	Vector3D centre = getCentre();
	Vector3D normal = (point - centre);
	Vector3D divisor = (vmin - vmax) / 2.0f;
	divisor.x = abs(divisor.x);
	divisor.y = abs(divisor.y);
	divisor.z = abs(divisor.z);

	const float bias = 1.000010f;

	normal = normal / divisor * bias;
	normal.x = floor(normal.x);
	normal.y = floor(normal.y);
	normal.z = floor(normal.z);

	return normal.unitVector();
}

BoundingBox Box::getBoundingBox() const {
	return BoundingBox(vmin, vmax);
}

Box Box::operator=(const Box &box) {
	return Box(box.vmin, box.vmax, box.getKA(), box.getKD(), box.getKS());
}

std::ostream& operator<<(std::ostream& os, const Box& rhs) {
	return os << (BoundingBox)rhs;
}
