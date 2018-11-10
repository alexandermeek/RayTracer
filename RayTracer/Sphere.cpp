#include "pch.h"
#include "Sphere.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <iostream>

using std::cout;
using std::endl;

Sphere::Sphere(Vector3D centre, float radius)
	: Object3D(FloatRGB(1,1,1), FloatRGB(1,1,1), FloatRGB(1,1,1)) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::~Sphere() {
}

Vector3D Sphere::getNormal(Vector3D point) {
	return (centre - point).unitVector();
}

bool Sphere::intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance) {
	Vector3D oC = rayOrigin - centre;
	float b = 2 * directionVector.dotProduct(oC);
	float a = directionVector.dotProduct(directionVector);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = std::pow(b, 2) - 4 * a * c;

	if (b24ac < 0) {
		return false;
	}

	float t;
	float t1 = (-b + std::sqrt(b24ac)) / 2 * a;
	float t2 = (-b - std::sqrt(b24ac)) / 2 * a;

	if (t1 < 0 || t2 < 0) {
		return false;
	}

	if (t1 < t2) {
		t = t1;
	} else {
		t = t2;
	}

	distance = t;
	point = rayOrigin + directionVector * t;

	return true;
}

std::string Sphere::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Sphere: {" << endl
		<< "    Point " << centre.toString() << endl
		<< "   Radius " << radius << endl << "}";
	return stream.str();
}
