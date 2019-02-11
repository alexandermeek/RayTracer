#include "pch.h"
#include "Sphere.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::cout;
using std::endl;

Sphere::Sphere(Vector3D centre, float radius)
	: Object3D(FloatRGB(1,1,1), FloatRGB(1,1,1), FloatRGB(1,1,1), UNIDIRECTIONAL) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS, UNIDIRECTIONAL) {
	this->centre = centre;
	this->radius = radius;
}

Sphere::~Sphere() {
}

Vector3D Sphere::getNormal(Vector3D point) {
	return (point - centre);
}

bool Sphere::intersect(Ray ray) {
	float t;
	return intersect(ray, t);
}

bool Sphere::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

bool Sphere::intersect(Ray ray, float& distance) {
	Vector3D oC = ray.origin - centre;
	float b = 2 * ray.direction.dotProduct(oC);
	float a = ray.direction.dotProduct(ray.direction);
	float c = oC.dotProduct(oC) - pow(radius, 2);
	float b24ac = pow(b, 2) - 4 * a * c;

	if (b24ac < 0) {
		return false;
	}

	float t;
	float t1 = (-b + sqrt(b24ac)) / 2.0f * a;
	float t2 = (-b - sqrt(b24ac)) / 2.0f * a;

	if (t1 < 0 || t2 < 0) {
		return false;
	}

	distance = t1 < t2 ? t1 : t2;

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
