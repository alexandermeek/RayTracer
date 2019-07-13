#include "pch.h"
#include "Sphere.h"

#include <math.h>
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

Vector3D Sphere::getNormal(Vector3D point) {
	return (point - centre);
}

BoundingBox Sphere::getBoundingBox() const {
	Vector3D vmin(centre.x - radius, centre.y - radius, centre.z - radius);
	Vector3D vmax(centre.x + radius, centre.y + radius, centre.z + radius);
	return BoundingBox(vmin, vmax);
}

bool Sphere::intersect(Ray ray, float& distance) {
	Vector3D oC = ray.origin - centre;
	float b = 2 * ray.direction.dotProduct(oC);
	float a = ray.direction.dotProduct(ray.direction);
	float c = oC.dotProduct(oC) - std::pow(radius, 2);
	float b24ac = std::pow(b, 2) - 4 * a * c;

	if (b24ac < 0) {
		return false;
	}

	float t1 = (-b + std::sqrt(b24ac)) / 2.0f * a;
	float t2 = (-b - std::sqrt(b24ac)) / 2.0f * a;

	if (t1 < 0 || t2 < 0) {
		return false;
	}

	distance = t1 < t2 ? t1 : t2;

	return true;
}

bool Sphere::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(point);

	return true;
}

std::ostream& operator<<(std::ostream& os, const Sphere& rhs) {
	os << std::fixed << std::setprecision(2)
		<< "Sphere: {" << endl
		<< "    Point " << rhs.centre << endl
		<< "          Radius: " << rhs.radius << endl << "}";
	return os;
}
