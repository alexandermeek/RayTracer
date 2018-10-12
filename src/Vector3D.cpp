#include "Vector3D.h"
#include <math.h>
#include <cmath>
#include <string>

Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3D::Vector3D(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D(const int a [3], const int b [3]) {
    this->x = b[0] - a[0];
    this->y = b[1] - a[1];
    this->z = b[2] - a[2];
}

Vector3D::~Vector3D() {
    //dtor
}

int Vector3D::getX() const {
    return this->x;
}

int Vector3D::getY() const {
    return this->y;
}

int Vector3D::getZ() const {
    return this->z;
}

void Vector3D::setX(int x) {
    this->x = x;
}

void Vector3D::setY(int y) {
    this->y = y;
}

void Vector3D::setZ(int z) {
    this->z = z;
}

double Vector3D::magnitude() const {
    int x,y,z;
    x = std::pow(this->x, 2);
    y = std::pow(this->y, 2);
    z = std::pow(this->z, 2);
    return sqrt(x + y + z);
}

double Vector3D::dotP(const Vector3D& v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

double Vector3D::cosTheta(const Vector3D& v) {
    double dotProduct = dotP(v);
    double magA = magnitude();
    double magB = v.magnitude();
    return dotProduct / (magA*magB);
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

Vector3D Vector3D::operator*(const int k) {
    Vector3D vect;
    vect.setX(x*k);
    vect.setY(y*k);
    vect.setZ(z*k);
    return vect;
}

Vector3D Vector3D::operator/(const int k) {
    Vector3D vect;
    vect.setX(x/k);
    vect.setY(y/k);
    vect.setZ(z/k);
    return vect;
}

std::string Vector3D::toString() {
    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}