#include "pch.h"
#include "Camera.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Camera::Camera() {
    //ctor
}

/*
Construcst a camera given it's position, what it's looking at,
and the size of the camera view.
*/
Camera::Camera(Vector3D vRP, Vector3D pRef, int width, int height) {
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

	pixels = new Vector3D[width*height];
	computePixels();
}

Camera::~Camera() {
    //dtor
}

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
Sets the width of the camera view.
Also re-calculates the pixel plane.
*/
void Camera::setWidth(int x) {
	width = x;
	computePixels();
}

/*
Sets the height of the camera view.
Also re-calculates the pixel plane.
*/
void Camera::setHeight(int y) {
	height = y;
	computePixels();
}

/*
Sets the view reference position.
Also re-calculates the pixel plane.
*/
void Camera::setVRP(Vector3D p) {
	viewReferencePoint = p;
	computePixels();
}

/*
Sets the view plane normal vector.
Also re-calculates the pixel plane.
*/
void Camera::setVPN(Vector3D v) {
	viewPlaneNormalVector = v.unitVector();
	computePixels();
}

/*
Sets the view up vector.
Also re-calculates the pixel plane.
*/
void Camera::setVUV(Vector3D v) {
	viewUpVector = v.unitVector();
	computePixels();
}

/*
Sets the view right vector.
Also re-calculates the pixel plane.
*/
void Camera::setVRV(Vector3D v) {
	viewRightVector = v.unitVector;
	computePixels();
}

/*
Gets a point downwards of given p at a distance k.
(In the perspective of the camera.)
*/
Vector3D Camera::getPointDown(Vector3D p, double k) {
	Vector3D manipulationVector = viewUpVector * k;
	Vector3D tempPoint;
	tempPoint.setX(p.getX() - manipulationVector.getX());
	tempPoint.setY(p.getY() - manipulationVector.getY());
	tempPoint.setZ(p.getZ() - manipulationVector.getZ());
	return tempPoint;
}

/*
Gets a point to the right of given p at a distance k.
(In the perspective of the camera.)
*/
Vector3D Camera::getPointRight(Vector3D p, double k) {
	Vector3D manipulationVector = viewRightVector * k;
	Vector3D tempPoint;
	tempPoint.setX(p.getX() + manipulationVector.getX());
	tempPoint.setY(p.getY() + manipulationVector.getY());
	tempPoint.setZ(p.getZ() + manipulationVector.getZ());
	return tempPoint;
}

/*
Gets the pixel position for pixel (x,y) in the camera view.
*/
Vector3D Camera::getPixelPosition(int x, int y) {
	return pixels[x * height + y];
}

/*
Calculates the position of each of the pixels in the camera.
*/
void Camera::computePixels() {
	//Finds the top left corner making sure the VRP is in the centre of the camera view.
	double x, y;
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
	pixels[0] = getPointDown(tempPoint, y);
	
	//For each pixel in the camera view.
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			pixels[i * height + j] = computePixel(i, j, pixels[0]);
		}
	}
}

Vector3D Camera::computePixel(int x, int y, Vector3D topLeftPixel) {
	Vector3D tempPoint = getPointRight(topLeftPixel, x);
	tempPoint = getPointDown(tempPoint, y);
	return tempPoint;
}

/*
Return the Camera object in string form. For debug purposes.
*/
std::string Camera::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Camera: {" << endl
		<< " Point " << viewReferencePoint.toString() << endl
		<< "Normal " << viewPlaneNormalVector.toString() << endl
		<< "    Up " << viewUpVector.toString() << endl
		<< " Right " << viewRightVector.toString() << endl << "}";
	return stream.str();
}
