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

/*
Gets the view reference point.
*/
Point3D Camera::getVRP() const {
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
Sets the view reference position.
*/
void Camera::setVRP(Point3D p) {
	viewReferencePoint = p;
}

/*
Sets the view plane normal vector.
*/
void Camera::setVPN(Vector3D v) {
	viewPlaneNormalVector = v;
}

/*
Sets the view up vector.
*/
void Camera::setVUV(Vector3D v) {
	viewUpVector = v;
}

/*
Sets the view right vector.
*/
void Camera::setVRV(Vector3D v) {
	viewRightVector = v;
}

/*
Gets a point upwards of given p at a distance k.
(In the perspective of the camera.
*/
Point3D Camera::getPointUp(Point3D p, double k) {
	Vector3D manipulationVector = viewUpVector * k;
	Point3D tempPoint;
	tempPoint.setX(p.getX() + manipulationVector.getX());
	tempPoint.setY(p.getY() + manipulationVector.getY());
	tempPoint.setZ(p.getZ() + manipulationVector.getZ());
	return tempPoint;
}

/*
Gets a point to the right of given p at a distance k.
(In the perspective of the camera.)
*/
Point3D Camera::getPointRight(Point3D p, double k) {
	Vector3D manipulationVector = viewRightVector * k;
	Point3D tempPoint;
	tempPoint.setX(p.getX() + manipulationVector.getX());
	tempPoint.setY(p.getY() + manipulationVector.getY());
	tempPoint.setZ(p.getZ() + manipulationVector.getZ());
	return tempPoint;
}

/*
Gets the array of pixel positions.
*/
Point3D* Camera::getPixels() {
	return pixels;
}

/*
Calculates the position of each of the pixels in the camera.
*/
void Camera::computePixels() {
	//Finds the top left corner making sure the VRP is in the centre of the camera view.
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
	
	//For each pixel in the camera view.
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			/*If you are at the top of a column of pixels (j=0), compute the value 
			for the first row.*/
			if (j == 0) {
				if (i != 0) {
					pixels[i * height + j] = getPointRight(pixels[0], i);
				}
			} else {
				/*Else work out the pixel position based off the position of the pixel 
				at the top of the column.*/
				pixels[i * height + j] = getPointUp(pixels[i * height], j * -1);
			}
		}
	}
}

/*
Return the Camera object in string form. For debug purposes.
*/
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
