#include "pch.h"
#include "Vector3D.h"

#include <math.h>
#include <cmath>

Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const double a [3], const double b [3]) {
    this->x = b[0] - a[0];
    this->y = b[1] - a[1];
    this->z = b[2] - a[2];
}

Vector3D::~Vector3D() {
    //dtor
}

double Vector3D::getX() const {
    return this->x;
}

double Vector3D::getY() const {
    return this->y;
}

double Vector3D::getZ() const {
    return this->z;
}

void Vector3D::setX(double x) {
    this->x = x;
}

void Vector3D::setY(double y) {
    this->y = y;
}

void Vector3D::setZ(double z) {
    this->z = z;
}

double Vector3D::magnitude() const {
	double x,y,z;
    x = std::pow(this->x, 2);
    y = std::pow(this->y, 2);
    z = std::pow(this->z, 2);
    return sqrt(x + y + z);
}

double Vector3D::dotProduct(const Vector3D& v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

Vector3D Vector3D::crossProduct(const Vector3D& v) {
	Vector3D tempVector;
	tempVector.setX(y * v.getZ() - z * v.getY());
	tempVector.setY(z * v.getX() - x * v.getZ());
	tempVector.setZ(x * v.getY() - y * v.getX());
	return tempVector;
}

double Vector3D::cosTheta(const Vector3D& v) {
    double dotProd = dotProduct(v);
    double magA = magnitude();
    double magB = v.magnitude();
    return dotProd / (magA*magB);
}

Vector3D Vector3D::unitVector() {
	return *this / this->magnitude();
}

Vector3D Vector3D::operator+(const Vector3D& v) {
    Vector3D vect;
    vect.setX(x + v.getX());
    vect.setY(y + v.getY());
    vect.setZ(z + v.getZ());
    return vect;
}

Vector3D Vector3D::operator-(const Vector3D& v) {
    Vector3D vect;
    vect.setX(x - v.getX());
    vect.setY(y - v.getY());
    vect.setZ(z - v.getZ());
    return vect;
}

Vector3D Vector3D::operator*(const double k) {
    Vector3D vect;
    vect.setX(x*k);
    vect.setY(y*k);
    vect.setZ(z*k);
    return vect;
}

Vector3D Vector3D::operator/(const double k) {
    Vector3D vect;
    vect.setX(x/k);
    vect.setY(y/k);
    vect.setZ(z/k);
    return vect;
}

std::string Vector3D::toString() {
    return "Vector: (" + std::to_string(x) + "," 
		+ std::to_string(y) + "," 
		+ std::to_string(z) + ")";
}
