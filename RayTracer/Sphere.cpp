#include "pch.h"
#include "Sphere.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <iostream>

using std::cout;
using std::endl;

Sphere::Sphere(Vector3D centre, float radius) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::~Sphere() {
}

bool Sphere::doesIntersect(Vector3D rayOrigin, Vector3D directionVector) {
	Vector3D oC = rayOrigin - centre;
	float b2 = std::pow(2 * directionVector.dotProduct(oC), 2);
	float a = directionVector.dotProduct(directionVector);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = b2 - 4 * a * c;

	//cout << b24ac;

	if (b24ac < 0) {
		return false;
	} else {
		return true;
	}
}

std::string Sphere::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Sphere: {" << endl
		<< " Point " << centre.toString() << endl
		<< "Radius " << radius << endl << "}";
	return stream.str();
}
