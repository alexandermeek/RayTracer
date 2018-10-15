#include "pch.h"
#include "Camera.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Camera::Camera() {
    //ctor
}

Camera::Camera(Point3D vRP, Point3D pRef, int width, int height) {
	Vector3D normal = pRef - vRP;
	Vector3D up(0, 1, 0);
	Vector3D right = up.crossProduct(normal);
	up = normal.crossProduct(right);

	viewReferencePoint = vRP;
	viewPlaneNormalVector = normal.unitVector();
	viewRightVector = right.unitVector();
	viewUpVector = up.unitVector();

	this->width = width;
	this->height = height;

	pixels = new Point3D[width*height];
	computePixels();
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

Point3D Camera::getPointUp(Point3D p, double k) {
	Vector3D manipulationVector = viewUpVector * k;
	Point3D tempPoint;
	tempPoint.setX(p.getX() + manipulationVector.getX());
	tempPoint.setY(p.getY() + manipulationVector.getY());
	tempPoint.setZ(p.getZ() + manipulationVector.getZ());
	return tempPoint;
}

Point3D Camera::getPointRight(Point3D p, double k) {
	Vector3D manipulationVector = viewRightVector * k;
	Point3D tempPoint;
	tempPoint.setX(p.getX() + manipulationVector.getX());
	tempPoint.setY(p.getY() + manipulationVector.getY());
	tempPoint.setZ(p.getZ() + manipulationVector.getZ());
	return tempPoint;
}

Point3D* Camera::getPixels() {
	return pixels;
}

void Camera::computePixels() {
	double x, y;
	if (width % 2 == 0) {
		x = (width / 2 - 0.5) * -1;
	} else {
		x = (width / 2) * -1;
	}
	if (height % 2 == 0) {
		y = (height / 2 - 0.5);
	} else {
		y = height / 2;
	}
	Point3D tempPoint = getPointRight(viewReferencePoint, x);
	pixels[0] = getPointUp(tempPoint, y);
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (j == 0) {
				if (i != 0) {
					pixels[i * height + j] = getPointRight(pixels[(i - 1) * height + j], 1);
				}
			} else {
				pixels[i * height + j] = getPointUp(pixels[i * height], (j * -1));
			}
		}
	}
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
