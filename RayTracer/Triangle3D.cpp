#include "pch.h"
#include "Triangle3D.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::cout;
using std::endl;

constexpr float kEpsilon = 1e-8;

Triangle3D::Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC)
	: Object3D(FloatRGB(1, 1, 1), FloatRGB(1, 1, 1), FloatRGB(1,1,1)) {
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

Triangle3D::Triangle3D(Vector3D pointA, Vector3D pointB, Vector3D pointC, FloatRGB kA, FloatRGB kD, FloatRGB kS)
	: Object3D(kA, kD, kS) {
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

Triangle3D::~Triangle3D()
{
}

Vector3D Triangle3D::getNormal(Vector3D point) {
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D normal = aB.crossProduct(aC).unitVector();

	return normal;
}

bool Triangle3D::intersect(Vector3D rayOrigin, Vector3D directionVector) {
	return false;
}

bool Triangle3D::intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance,
	PointLight& light, FloatRGB& colour) {
	float t, u, v;

	Vector3D normal = getNormal(Vector3D());
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D planeVector = directionVector.crossProduct(aC).unitVector();
	float det = aB.dotProduct(planeVector);
	if (det < kEpsilon) return false;

	if (fabs(det) < kEpsilon) return false;

	float invDet = 1 / det;
	Vector3D tVec = (rayOrigin - pointA).unitVector();
	u = tVec.dotProduct(planeVector) * invDet;
	if (u < 0 || u > 1) return false;

	Vector3D qVec = (tVec.crossProduct(aB) * invDet).unitVector();
	v = tVec.dotProduct(qVec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = aC.dotProduct(qVec) * invDet;
	if (t < 0) return false;

	distance = t;
	point = rayOrigin + directionVector * t;

	Vector3D C;

	Vector3D edge0 = pointB - pointA;
	Vector3D vp0 = point - pointB;
	C = edge0.crossProduct(vp0);
	//if (normal.dotProduct(C) < 0) return false;

	Vector3D edge1 = pointC - pointA;
	Vector3D vp1 = point - pointB;
	C = edge1.crossProduct(vp1);
	if ((u = normal.dotProduct(C)) < 0) return false;

	Vector3D edge2 = pointA - pointB;
	Vector3D vp2 = point - pointC;
	C = edge2.crossProduct(vp2);
	if ((v = normal.dotProduct(C)) < 0) return false;


	colour = getColourValue(objects, point, light, rayOrigin);

	return true;
}

FloatRGB Triangle3D::getColourValue(std::vector<Object3D*>& objects, Vector3D point, PointLight& light, Vector3D rayOrigin) {
	Vector3D normal = getNormal(point);
	return Object3D::getColourValue(objects, point, normal, light, rayOrigin);
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