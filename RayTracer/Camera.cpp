#include "pch.h"
#include "Camera.h"

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
	return "ViewRef " + viewReferencePoint.toString() 
		+ ", Normal " + viewPlaneNormalVector.toString() 
		+ ", Up " + viewUpVector.toString() 
		+ ", Right " + viewRightVector.toString();
}
