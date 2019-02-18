#include "pch.h"
#include "Triangle3D.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Triangle3D::Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC)
	: Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1,1,1), BIDIRECTIONAL) {
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

Triangle3D::Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS, BIDIRECTIONAL) {
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

Triangle3D::~Triangle3D() {
}

Vector3D Triangle3D::getPointA() {
	return pointA;
}

Vector3D Triangle3D::getPointB() {
	return pointB;
}

Vector3D Triangle3D::getPointC() {
	return pointC;
}

Vector3D Triangle3D::getCentre() {
	Vector3D centre = pointA + pointB + pointC / 3;
	return centre;
}

Vector3D Triangle3D::getNormal(Vector3D point) {
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D normal = aB.crossProduct(aC);

	return normal;
}

bool Triangle3D::intersect(Ray ray) {
	float t;
	return intersect(ray, t);
}

bool Triangle3D::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(Vector3D());

	return true;
}

bool Triangle3D::intersect(Ray ray, float& distance) {
	float t, u, v;

	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D planeVector = ray.direction.crossProduct(aC);
	float det = aB.dotProduct(planeVector);
	if (det > -EPSILON && det < EPSILON) return false;

	if (fabs(det) < EPSILON) return false;

	float invDet = 1 / det;
	Vector3D tVec = ray.origin - pointA;
	u = tVec.dotProduct(planeVector) * invDet;
	if (u < 0 || u > 1) return false;

	Vector3D qVec = tVec.crossProduct(aB);
	v = ray.direction.dotProduct(qVec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = aC.dotProduct(qVec) * invDet;
	if (t < EPSILON) return false;

	distance = t;

	return true;
}

std::string Triangle3D::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Triangle: {" << endl
		<< "   PointA " << pointA.toString() << endl
		<< "   PointB " << pointB.toString() << endl
		<< "   PointC " << pointC.toString() << endl << "}";
	return stream.str();
}