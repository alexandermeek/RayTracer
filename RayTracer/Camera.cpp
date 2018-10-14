#include "pch.h"
#include "Camera.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Camera::Camera() {
    //ctor
}

Camera::Camera(Point3D vRP, Point3D pRef) {
	Vector3D normal = pRef - vRP;
	Vector3D up(0, 1, 0);
	Vector3D right = up.crossProduct(normal);
	up = normal.crossProduct(right);

	viewReferencePoint = vRP;
	viewPlaneNormalVector = normal.unitVector();
	viewRightVector = right.unitVector();
	viewUpVector = up.unitVector();
}

Camera::~Camera() {
    //dtor
}

Point3D Camera::getVRP() const {
	return viewReferencePoint;
}

Vector3D Camera::getVPN() const {
	return viewPlaneNormalVector;
}

Vector3D Camera::getVUV() const {
	return viewUpVector;
}

Vector3D Camera::getVRV() const {
	return viewRightVector;
}

void Camera::setVRP(Point3D p) {
	viewReferencePoint = p;
}

void Camera::setVPN(Vector3D v) {
	viewPlaneNormalVector = v;
}

void Camera::setVUV(Vector3D v) {
	viewUpVector = v;
}

void Camera::setVRV(Vector3D v) {
	viewRightVector = v;
}

std::string Camera::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Camera: {" << endl
		<< "        " << viewReferencePoint.toString() << endl
		<< "Normal " << viewPlaneNormalVector.toString() << endl
		<< "    Up " << viewUpVector.toString() << endl
		<< " Right " << viewRightVector.toString() << endl << "}";
	return stream.str();
}
