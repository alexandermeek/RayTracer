#include "pch.h"
#include "Camera.h"

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::cout;
using std::endl;

Camera::Camera() {
    //ctor
}

/*
Constructs a camera given it's position, what it's looking at,
and the size of the camera view.
*/
Camera::Camera(Vector3D vRP, Vector3D pRef, int width, int height, float scale, int type) {
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
	this->scale = scale;
	this->type = type;

	this->meanSize = (float)width + (float)height / 2.0f;

	rays = new Ray[width*height];
	computeRays();
}

Camera::~Camera() {}

/*
Gets the width of the camera view.
*/
int Camera::getWidth() const {
	return width;
}

/*
Gets the height of the camera view.
*/
int Camera::getHeight() const {
	return height;
}

/*
Gets the view reference point.
*/
Vector3D Camera::getVRP() const {
	return viewReferencePoint;
}

/*
Gets the view plane normal vector.
*/
Vector3D Camera::getVPN() const {
	return viewPlaneNormalVector;
}

/*
Gets the view up vector.
*/
Vector3D Camera::getVUV() const {
	return viewUpVector;
}

/*
Gets the view right vector.
*/
Vector3D Camera::getVRV() const {
	return viewRightVector;
}

/*
Gets a point downwards of given p at a distance k.
(In the perspective of the camera.)
*/
Vector3D Camera::getPointDown(Vector3D p, float k) {
	float tempScale = type == 0 ? 100 / scale / meanSize : 1;
	Vector3D manipulationVector = viewUpVector * k * tempScale;
	Vector3D tempPoint;
	tempPoint.x = p.x - manipulationVector.x;
	tempPoint.y = p.y - manipulationVector.y;
	tempPoint.z = p.z - manipulationVector.z;
	return tempPoint;
}

/*
Gets a point to the right of given p at a distance k.
(In the perspective of the camera.)
*/
Vector3D Camera::getPointRight(Vector3D p, float k) {
	float tempScale = type == 0 ? 100 / scale / meanSize : 1;
	Vector3D manipulationVector = viewRightVector * k * tempScale;
	Vector3D tempPoint;
	tempPoint.x = p.x + manipulationVector.x;
	tempPoint.y = p.y + manipulationVector.y;
	tempPoint.z = p.z + manipulationVector.z;
	return tempPoint;
}

/*
Gets a point to the forwards of given p at a distance k.
(In the perspective of the camera.)
*/
Vector3D Camera::getPointForward(Vector3D p, float k) {
	Vector3D manipulationVector = viewPlaneNormalVector * k * meanSize;
	Vector3D tempPoint;
	tempPoint.x = p.x + manipulationVector.x;
	tempPoint.y = p.y + manipulationVector.y;
	tempPoint.z = p.z + manipulationVector.z;
	return tempPoint;
}

/*
Gets the pixel position for pixel (x,y) in the camera view.
*/
Ray Camera::getRayAtPosition(int x, int y) {
	return rays[x + y * width];
}

/*
Calculates the position of each of the pixels in the camera.
*/
void Camera::computeRays() {
	//Finds the top left corner making sure the VRP is in the centre of the camera view.
	float x, y;
	if (width % 2 == 0) {
		x = (width / 2 - 0.5);
	} else {
		x = (width / 2);
	}
	if (height % 2 == 0) {
		y = (height / 2 - 0.5);
	} else {
		y = (height / 2);
	}

	/*x and y need to be in the opposite direction since the methods used to get the top
	left corner are getPointDown and getPointRight.*/
	x *= -1;
	y *= -1;
	
	Vector3D tempPoint = getPointRight(viewReferencePoint, x);
	tempPoint = getPointDown(tempPoint, y);
	tempPoint = type == 0 ? tempPoint : getPointForward(tempPoint, scale);
	
	//For each pixel in the camera view.
	#pragma omp parallel for
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			rays[i + j * width] = computeRay(i, j, tempPoint);
		}
	}

	cout << rays[0].toString();
}

Ray Camera::computeRay(int x, int y, Vector3D topLeftPixel) {
	Vector3D tempPoint = getPointRight(topLeftPixel, x);
	tempPoint = getPointDown(tempPoint, y);

	Vector3D rayOrigin = type == 0 ? tempPoint : viewReferencePoint;
	Vector3D rayDirection = type == 0 ? viewPlaneNormalVector : tempPoint - viewReferencePoint;
	return Ray (rayOrigin, rayDirection.unitVector());
}

/*
Return the Camera object in string form. For debug purposes.
*/
std::string Camera::toString() {
	std::string type = this->type == 0 ? "Orthographic" : "Perspective";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Camera: {" << endl
		<< "    Point " << viewReferencePoint.toString() << endl
		<< "   Normal " << viewPlaneNormalVector.toString() << endl
		<< "       Up " << viewUpVector.toString() << endl
		<< "    Right " << viewRightVector.toString() << endl
		<< "       View Size: " << width << "x" << height << endl
		<< " Projection Type: " << type
		<< endl << "}";
	return stream.str();
}
