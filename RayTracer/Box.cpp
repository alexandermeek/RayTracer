#include "pch.h"
#include "Box.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::cout;
using std::endl;

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

bool Box::intersect(Ray ray) {
	float t;
	return intersect(ray, t);
}

bool Box::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

bool Box::intersect(Ray ray, float& distance) {
	Vector3D t0 = (vmin - ray.origin) / ray.direction;
	Vector3D t1 = (vmax - ray.origin) / ray.direction;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	bool invDirNegative = ray.direction.inverse().x < 0;
	tmin = invDirNegative ? t1.x : t0.x;
	tmax = invDirNegative ? t0.x : t1.x;

	invDirNegative = ray.direction.inverse().y < 0;
	tymin = invDirNegative ? t1.y : t0.y;
	tymax = invDirNegative ? t0.y : t1.y;

	invDirNegative = ray.direction.inverse().z < 0;
	tzmin = invDirNegative ? t1.z : t0.z;
	tzmax = invDirNegative ? t0.z : t1.z;

	if (tmin > tymax || tymin > tmax) return false;
	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;


	if (tmin > tzmax || tzmin > tmax) return false;
	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	float t = tmin;
	if (t < 0) {
		t = tmax;
		if (t < 0) return false;
	}

	distance = t;

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

Vector3D Box::getCentre() {
	float x, y, z;
	x = vmin.x + ((vmax.x - vmin.x) / 2.0f);
	y = vmin.y + ((vmax.y - vmin.y) / 2.0f);
	z = vmin.z + ((vmax.z - vmin.z) / 2.0f);
	return Vector3D(x, y, z);
}

std::string Box::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Box: {" << endl
		<< "   vmin " << vmin.toString() << endl
		<< "   vmax " << vmax.toString() << endl << "}";
	return stream.str();
}
