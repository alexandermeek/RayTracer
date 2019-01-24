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

bool Box::intersect(Vector3D rayOrigin, Vector3D directionVector) {

	Vector3D t0 = (vmin - rayOrigin) / directionVector;
	Vector3D t1 = (vmax - rayOrigin) / directionVector;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (t0.getX() > t1.getX()) {
		tmin = t1.getX();
		tmax = t0.getX();
	}
	else {
		tmin = t0.getX();
		tmax = t1.getX();
	}

	if (t0.getY() > t1.getY()) {
		tymin = t1.getY();
		tymax = t0.getY();
	}
	else {
		tymin = t0.getY();
		tymax = t1.getY();
	}

	if (t0.getZ() > t1.getZ()) {
		tzmin = t1.getZ();
		tzmax = t0.getZ();
	}
	else {
		tzmin = t0.getZ();
		tzmax = t1.getZ();
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

bool Box::intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, Vector3D& normal,
	float& distance) {

	Vector3D t0 = (vmin - rayOrigin) / directionVector;
	Vector3D t1 = (vmax - rayOrigin) / directionVector;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (t0.getX() > t1.getX()) {
		tmin = t1.getX();
		tmax = t0.getX();
	}
	else {
		tmin = t0.getX();
		tmax = t1.getX();
	}

	if (t0.getY() > t1.getY()) {
		tymin = t1.getY();
		tymax = t0.getY();
	}
	else {
		tymin = t0.getY();
		tymax = t1.getY();
	}

	if (t0.getZ() > t1.getZ()) {
		tzmin = t1.getZ();
		tzmax = t0.getZ();
	}
	else {
		tzmin = t0.getZ();
		tzmax = t1.getZ();
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
	point = rayOrigin + directionVector * t;
	normal = getNormal(point);

	return true;
}

Vector3D Box::getNormal(Vector3D point) {
	Vector3D centre = getCentre();
	Vector3D normal = (centre - point).unitVector();
	float x, y, z;
	x = abs(normal.getX());
	y = abs(normal.getY());
	z = abs(normal.getZ());

	if (x >= y && x >= z) {
		normal.setY(0);
		normal.setZ(0);
	} 
	else {
		if (y >= x && y >= z) {
			normal.setX(0);
			normal.setZ(0);
		}
		else {
			normal.setX(0);
			normal.setY(0);
		}
	}
	return normal;
}

Vector3D Box::getCentre() {
	float x, y, z;
	x = vmin.getX() + ((vmax.getX() - vmin.getX()) / 2.0f);
	y = vmin.getY() + ((vmax.getY() - vmin.getY()) / 2.0f);
	z = vmin.getZ() + ((vmax.getZ() - vmin.getZ()) / 2.0f);
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
