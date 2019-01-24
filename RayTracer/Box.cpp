#include "pch.h"
#include "Box.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::cout;
using std::endl;

Box::Box(Vector3D vmin, Vector3D vmax) {
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

	Vector3D t0 = (vmin - ray.origin) / ray.direction;
	Vector3D t1 = (vmax - ray.origin) / ray.direction;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (t0.x > t1.x) {
		tmin = t1.x;
		tmax = t0.x;
	}
	else {
		tmin = t0.x;
		tmax = t1.x;
	}

	if (t0.y > t1.y) {
		tymin = t1.y;
		tymax = t0.y;
	}
	else {
		tymin = t0.y;
		tymax = t1.y;
	}

	if (t0.z > t1.z) {
		tzmin = t1.z;
		tzmax = t0.z;
	}
	else {
		tzmin = t0.z;
		tzmax = t1.z;
	}

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

	return true;
}

bool Box::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {

	Vector3D t0 = (vmin - ray.origin) / ray.direction;
	Vector3D t1 = (vmax - ray.origin) / ray.direction;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (t0.x > t1.x) {
		tmin = t1.x;
		tmax = t0.x;
	}
	else {
		tmin = t0.x;
		tmax = t1.x;
	}

	if (t0.y > t1.y) {
		tymin = t1.y;
		tymax = t0.y;
	}
	else {
		tymin = t0.y;
		tymax = t1.y;
	}

	if (t0.z > t1.z) {
		tzmin = t1.z;
		tzmax = t0.z;
	}
	else {
		tzmin = t0.z;
		tzmax = t1.z;
	}

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
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

Vector3D Box::getNormal(Vector3D point) {
	Vector3D centre = getCentre();
	Vector3D normal = (centre - point).unitVector();
	float x, y, z;
	x = abs(normal.x);
	y = abs(normal.y);
	z = abs(normal.z);

	if (x >= y && x >= z) {
		normal.y = 0;
		normal.z = 0;
	} 
	else {
		if (y >= x && y >= z) {
			normal.x = 0;
			normal.z = 0;
		}
		else {
			normal.x = 0;
			normal.y = 0;
		}
	}
	return normal;
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
