#include "pch.h"
#include "Sphere.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <iostream>

using std::cout;
using std::endl;

Sphere::Sphere(Vector3D centre, float radius, ColourRGB colour) {
	this->centre = centre;
	this->radius = radius;
	this->colour = colour;
}

Sphere::~Sphere() {
}

bool Sphere::doesIntersect(Vector3D rayOrigin, Vector3D directionVector) {
	Vector3D oC = rayOrigin - centre;
	float b2 = std::pow(2 * directionVector.dotProduct(oC), 2);
	float a = directionVector.dotProduct(directionVector);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = b2 - 4 * a * c;

	if (b24ac < 0) {
		return false;
	} else {
		return true;
	}
}

Vector3D Sphere::getNormal(Vector3D point) {
	return centre - point;
}

bool Sphere::intersect(Vector3D rayOrigin, Vector3D directionVector, ColourRGB& colour) {
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

	Vector3D intersectionPoint = rayOrigin + directionVector * t;
	Vector3D normal = getNormal(intersectionPoint);
	normal = normal.unitVector();
	Vector3D lightDirection = intersectionPoint - Vector3D (500, 500, 500);
	lightDirection = lightDirection.unitVector();

	colour = (this->colour * 1 + this->colour * normal.dotProduct(lightDirection)) * 0.5;

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
