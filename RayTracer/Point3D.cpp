#include "pch.h"
#include "Point3D.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

/*
Creates a default point.
*/
Point3D::Point3D() {
	x = 0;
	y = 0;
	z = 0;
}

/*
Creates a point with given x,y,z values.
*/
Point3D::Point3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D::~Point3D() {
}

/*
Gets the x value.
*/
double Point3D::getX() const {
	return x;
}

/*
Gets the y value.
*/
double Point3D::getY() const {
	return y;
}

/*
Gets the z value.
*/
double Point3D::getZ() const {
	return z;
}

/*
Sets the x value.
*/
void Point3D::setX(double x) {
	this->x = x;
}

/*
Sets the y value.
*/
void Point3D::setY(double y) {
	this->y = y;
}

/*
Sets the z value.
*/
void Point3D::setZ(double z) {
	this->z = z;
}

/*
Returns the relative vector if two points are subtracted.
*/
Vector3D Point3D::operator-(const Point3D& p) {
	Vector3D tempVector;
	tempVector.setX(x - p.getX());
	tempVector.setY(y - p.getY());
	tempVector.setZ(z - p.getZ());
	return tempVector;
}

/*
Return the Point object in string form. For debug purposes.
*/
std::string Point3D::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Point: (" << x << "," << y << "," << z << ")";
	return stream.str();
}