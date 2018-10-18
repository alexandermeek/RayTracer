#include "pch.h"
#include "Vector3D.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

/*
Creates a default vector.
*/
Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

/*
Creates a vector with given x,y,z values.
*/
Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D() {
    //dtor
}

/*
Gets the x value.
*/
float Vector3D::getX() const {
    return this->x;
}

/*
Gets the y value.
*/
float Vector3D::getY() const {
    return this->y;
}

/*
Gets the z value.
*/
float Vector3D::getZ() const {
    return this->z;
}

/*
Sets the x value.
*/
void Vector3D::setX(float x) {
    this->x = x;
}

/*
Sets the y value.
*/
void Vector3D::setY(float y) {
    this->y = y;
}

/*
Sets the z value.
*/
void Vector3D::setZ(float z) {
    this->z = z;
}

/*
Calculates the magnitude of a vector.
*/
float Vector3D::magnitude() const {
	float x,y,z;
    x = std::pow(this->x, 2);
    y = std::pow(this->y, 2);
    z = std::pow(this->z, 2);
    return sqrt(x + y + z);
}

/*
Calculates the dot product of this vector and the given vector v.
Returns a scalar value.
*/
float Vector3D::dotProduct(const Vector3D& v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

/*
Calculates the cross product of this vector and the given vector v.
Returns a vector.
*/
Vector3D Vector3D::crossProduct(const Vector3D& v) {
	Vector3D tempVector;
	tempVector.setX(y * v.getZ() - z * v.getY());
	tempVector.setY(z * v.getX() - x * v.getZ());
	tempVector.setZ(x * v.getY() - y * v.getX());
	return tempVector;
}

/*
Calculates the cos theta between this vector and the given vector v.
Can be used to get the angle between vectors.
*/
float Vector3D::cosTheta(const Vector3D& v) {
	float dotProd = dotProduct(v);
	float magA = magnitude();
	float magB = v.magnitude();
    return dotProd / (magA*magB);
}

/*
Calculates the unit vector of this vector.
*/
Vector3D Vector3D::unitVector() {
	return *this / this->magnitude();
}

/*
Adds two vectors together.
*/
Vector3D Vector3D::operator+(const Vector3D& v) {
    Vector3D vect;
    vect.setX(x + v.getX());
    vect.setY(y + v.getY());
    vect.setZ(z + v.getZ());
    return vect;
}

/*
Subtracts two vectors.
*/
Vector3D Vector3D::operator-(const Vector3D& v) {
    Vector3D vect;
    vect.setX(x - v.getX());
    vect.setY(y - v.getY());
    vect.setZ(z - v.getZ());
    return vect;
}

/*
Multiplies this vector by a scalar value.
*/
Vector3D Vector3D::operator*(const float k) {
    Vector3D vect;
    vect.setX(x*k);
    vect.setY(y*k);
    vect.setZ(z*k);
    return vect;
}

/*
Divides this vector by a scalar value.
*/
Vector3D Vector3D::operator/(const float k) {
    Vector3D vect;
    vect.setX(x/k);
    vect.setY(y/k);
    vect.setZ(z/k);
    return vect;
}

/*
Return the Vector object in string form. For debug purposes.
*/
std::string Vector3D::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Vector: (" << x << "," << y << "," << z << ")";
	return stream.str();
}
