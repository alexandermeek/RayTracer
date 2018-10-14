#include "pch.h"
#include "Camera.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Camera::Camera() {
    //ctor
}

Camera::Camera(Point3D vRP, Point3D pRef) {
	viewReferencePoint = vRP;
	
	Vector3D normal = pRef - vRP;
	Vector3D up(0, 1, 0);
	Vector3D right = up.crossProduct(normal);

	viewPlaneNormalVector = normal.unitVector();
	viewRightVector = right.unitVector();

	up = normal.crossProduct(right);

	viewUpVector = up.unitVector();
}

Camera::~Camera() {
    //dtor
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
