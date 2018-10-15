#include "pch.h"
#include "Point3D.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

Point3D::Point3D() {
	x = 0;
	y = 0;
	z = 0;
}

Point3D::Point3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3D::~Point3D() {
}

double Point3D::getX() const {
	return x;
}

double Point3D::getY() const {
	return y;
}

double Point3D::getZ() const {
	return z;
}

void Point3D::setX(double x) {
	this->x = x;
}

void Point3D::setY(double y) {
	this->y = y;
}

void Point3D::setZ(double z) {
	this->z = z;
}

Vector3D Point3D::operator-(const Point3D& p) {
	Vector3D tempVector;
	tempVector.setX(x - p.getX());
	tempVector.setY(y - p.getY());
	tempVector.setZ(z - p.getZ());
	return tempVector;
}

std::string Point3D::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Point: (" << x << "," << y << "," << z << ")";
	return stream.str();
}