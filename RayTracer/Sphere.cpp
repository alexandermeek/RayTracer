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
	this->kA = 0.5;
	this->kD = 0.5;
	this->kS = 0.5;
}

Sphere::Sphere(Vector3D centre, float radius, ColourRGB colour, float kA, float kD, float kS) {
	this->centre = centre;
	this->radius = radius;
	this->colour = colour;
	this->kA = kA;
	this->kD = kD;
	this->kS = kS;
}

Sphere::~Sphere() {
}

ColourRGB Sphere::getColour() {
	return this->colour;
}

float Sphere::getKA() {
	return this->kA;
}

float Sphere::getKD() {
	return this->kD;
}

float Sphere::getKS() {
	return this->kS;
}

Vector3D Sphere::getNormal(Vector3D point) {
	return (centre - point).unitVector();
}

bool Sphere::intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point) {
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
