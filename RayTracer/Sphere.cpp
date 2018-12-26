#include "pch.h"
#include "Sphere.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Sphere::Sphere(Vector3D centre, float radius)
	: Object3D(FloatRGB(1,1,1), FloatRGB(1,1,1), FloatRGB(1,1,1), false) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS, false) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::~Sphere() {
}

Vector3D Sphere::getNormal(Vector3D point) {
	return (centre - point).unitVector();
}

bool Sphere::intersect(Vector3D rayOrigin, Vector3D directionVector) {
	Vector3D oC = rayOrigin - centre;
	float b = 2 * directionVector.dotProduct(oC);
	float a = directionVector.dotProduct(directionVector);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = std::pow(b, 2) - 4 * a * c;

	if (b24ac < 0) {
		return false;
	}

	float t;
	float t1 = (-b + std::sqrt(b24ac)) / 2.0f * a;
	float t2 = (-b - std::sqrt(b24ac)) / 2.0f * a;

	if (t1 < 0 || t2 < 0) {
		return false;
	}

	return true;
}

bool Sphere::intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, Vector3D& normal,
	float& distance, PointLight& light) {
	Vector3D oC = rayOrigin - centre;
	float b = 2 * directionVector.dotProduct(oC);
	float a = directionVector.dotProduct(directionVector);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = std::pow(b, 2) - 4 * a * c;

	if (b24ac < 0) {
		return false;
	}

	float t;
	float t1 = (-b + std::sqrt(b24ac)) / 2.0f * a;
	float t2 = (-b - std::sqrt(b24ac)) / 2.0f * a;

	if (t1 < 0 || t2 < 0) {
		return false;
	}

	t = t1 < t2 ? t1 : t2;

	distance = t;
	point = rayOrigin + directionVector * t;
	normal = getNormal(point);

	return true;
}

std::string Sphere::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Sphere: {" << endl
		<< "    Point " << centre.toString() << endl
		<< "          Radius: " << radius << endl << "}";
	return stream.str();
}
