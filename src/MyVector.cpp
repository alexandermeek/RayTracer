#include "MyVector.h"
#include <math.h>
#include <cmath>
#include <string>

MyVector::MyVector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

MyVector::MyVector(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

MyVector::MyVector(const int a [3], const int b [3]) {
    this->x = b[0] - a[0];
    this->y = b[1] - a[1];
    this->z = b[2] - a[2];
}

MyVector::~MyVector() {
    //dtor
}

double MyVector::magnitude() {
    int x,y,z;
    x = std::pow(this->x, 2);
    y = std::pow(this->y, 2);
    z = std::pow(this->z, 2);
    return sqrt(x + y + z);
}

int MyVector::getX() const {
    return this->x;
}

int MyVector::getY() const {
    return this->y;
}

int MyVector::getZ() const {
    return this->z;
}

void MyVector::setX(int x) {
    this->x = x;
}

void MyVector::setY(int y) {
    this->y = y;
}

void MyVector::setZ(int z) {
    this->z = z;
}

double MyVector::dotP(const MyVector& v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

MyVector MyVector::operator+(const MyVector& v) {
    MyVector vect;
    vect.setX(x + v.getX());
    vect.setY(y + v.getY());
    vect.setZ(z + v.getZ());
    return vect;
}

MyVector MyVector::operator-(const MyVector& v) {
    MyVector vect;
    vect.setX(x - v.getX());
    vect.setY(y - v.getY());
    vect.setZ(z - v.getZ());
    return vect;
}

MyVector MyVector::operator*(const int k) {
    MyVector vect;
    vect.setX(x*k);
    vect.setY(y*k);
    vect.setZ(z*k);
    return vect;
}

MyVector MyVector::operator/(const int k) {
    MyVector vect;
    vect.setX(x/k);
    vect.setY(y/k);
    vect.setZ(z/k);
    return vect;
}

std::string MyVector::toString() {
    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}
