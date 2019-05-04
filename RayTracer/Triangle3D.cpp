#include "pch.h"
#include "Triangle3D.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;
using std::fmax;
using std::fmin;

Triangle3D::Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC)
	: Object3D(FloatRGB(0.3, 0.3, 0.3), FloatRGB(0.3, 0.3, 0.3), FloatRGB(0.3,0.3,0.3), BIDIRECTIONAL) {
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

Vector3D Triangle3D::getPointA() const {
	return pointA;
}

Vector3D Triangle3D::getPointB() const {
	return pointB;
}

Vector3D Triangle3D::getPointC() const {
	return pointC;
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

bool Triangle3D::intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) {
	float t;
	if (!intersect(ray, t)) return false;

	distance = t;
	point = ray.origin + ray.direction * t;
	normal = getNormal(Vector3D());

	return true;
}

Vector3D Triangle3D::getNormal(Vector3D point) {
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D normal = aB.crossProduct(aC);

	return normal;
}

BoundingBox Triangle3D::getBoundingBox() const {
	Vector3D vmax, vmin;
	vmax.x = fmax(pointA.x, fmax(pointB.x, pointC.x));
	vmax.y = fmax(pointA.y, fmax(pointB.y, pointC.y));
	vmax.z = fmax(pointA.z, fmax(pointB.z, pointC.z));
	vmin.x = fmin(pointA.x, fmin(pointB.x, pointC.x));
	vmin.y = fmin(pointA.y, fmin(pointB.y, pointC.y));
	vmin.z = fmin(pointA.z, fmin(pointB.z, pointC.z));
	return BoundingBox(vmin, vmax);
}

std::ostream& operator<<(std::ostream& os, const Triangle3D& rhs) {
	os << std::fixed << std::setprecision(2);
	os << "Triangle: {" << endl
		<< "   PointA " << rhs.getPointA() << endl
		<< "   PointB " << rhs.getPointB() << endl
		<< "   PointC " << rhs.getPointC() << endl << "}";
	return os;
}