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
float Vector3D::dotProduct(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

/*
Calculates the cross product of this vector and the given vector v.
Returns a vector.
*/
Vector3D Vector3D::crossProduct(const Vector3D& v) const {
	Vector3D tempVector;
	tempVector.x = y * v.z - z * v.y;
	tempVector.y = z * v.x - x * v.z;
	tempVector.z = x * v.y - y * v.x;
	return tempVector;
}

/*
Calculates the cos theta between this vector and the given vector v.
Can be used to get the angle between vectors.
*/
float Vector3D::cosTheta(const Vector3D& v) const {
	float dotProd = dotProduct(v);
	float magA = magnitude();
	float magB = v.magnitude();
    return dotProd / (magA*magB);
}

/*
Calculates the unit vector of this vector.
*/
Vector3D Vector3D::unitVector() const {
	return *this / this->magnitude();
}

/*
Calculates the inverse of this vector.
*/
Vector3D Vector3D::inverse() const {
	Vector3D vect;
	vect.x = 1.0f / x;
	vect.y = 1.0f / y;
	vect.z = 1.0f / z;
	return vect;
}

/*
Adds two vectors together.
*/
Vector3D Vector3D::operator+(const Vector3D& v) const {
    Vector3D vect;
    vect.x = x + v.x;
    vect.y = y + v.y;
    vect.z = z + v.z;
    return vect;
}

/*
Subtracts two vectors.
*/
Vector3D Vector3D::operator-(const Vector3D& v) const {
    Vector3D vect;
    vect.x = x - v.x;
    vect.y = y - v.y;
    vect.z = z - v.z;
    return vect;
}

/*
Multiplies this vector by a scalar value.
*/
Vector3D Vector3D::operator*(const float k) const {
    Vector3D vect;
    vect.x = x*k;
    vect.y = y*k;
    vect.z = z*k;
    return vect;
}

/*
Divides this vector by a scalar value.
*/
Vector3D Vector3D::operator/(const float k) const {
    Vector3D vect;
    vect.x = x/k;
    vect.y = y/k;
    vect.z = z/k;
    return vect;
}

Vector3D Vector3D::operator/(const Vector3D& v) const {
	Vector3D vect;
	vect.x = x / v.x;
	vect.y = y / v.y;
	vect.z = z / v.z;
	return vect;
}

/*
Return the Vector object in string form. For debug purposes.
*/
std::string Vector3D::toString() const {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Vector: (" << x << "," << y << "," << z << ")";
	return stream.str();
}
