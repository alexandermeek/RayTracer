#include "pch.h"
#include "Camera.h"

Camera::Camera() {
    //ctor
}

Camera::Camera(Point3D vRP, Point3D pRef) {
	viewReferencePoint = vRP;
	viewPlaneNormalVector = pRef - vRP;
	viewUpVector = Vector3D(0, 1, 0);
	//viewRightVector = 
}

Camera::~Camera() {
    //dtor
}
