#include "pch.h"
#include "Triangle3D.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

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
	float t, u, v;
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D pVec = directionVector.crossProduct(aC).unitVector();
	float det = aB.dotProduct(pVec);

	if (det < 0) return false;

	float invDet = 1 / det;
	Vector3D tVec = (rayOrigin - pointA).unitVector();
	u = tVec.dotProduct(pVec) * invDet;
	if (u < 0 || u < 1) return false;

	Vector3D qVec = (tVec.crossProduct(qVec) * invDet).unitVector();
	v = tVec.dotProduct(qVec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = aC.dotProduct(qVec) * invDet;
	return true;
}

bool Triangle3D::intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance,
	PointLight& light, FloatRGB& colour) {
	float t, u, v;
	Vector3D aB = pointB - pointA;
	Vector3D aC = pointC - pointA;
	Vector3D pVec = directionVector.crossProduct(aC).unitVector();
	float det = aB.dotProduct(pVec);

	if (det < 0) return false;

	float invDet = 1 / det;
	Vector3D tVec = (rayOrigin - pointA).unitVector();
	u = tVec.dotProduct(pVec) * invDet;
	if (u < 0 || u < 1) return false;

	Vector3D qVec = (tVec.crossProduct(qVec) * invDet).unitVector();
	v = tVec.dotProduct(qVec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = aC.dotProduct(qVec) * invDet;

	distance = t;
	point = rayOrigin + directionVector * t;
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