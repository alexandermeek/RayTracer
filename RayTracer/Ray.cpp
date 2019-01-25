#include "pch.h"
#include "Ray.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

Ray::Ray() {
	this->origin = Vector3D(0, 0, 0);
	this->direction = Vector3D(0, 0, 0);
}

Ray::Ray(Vector3D origin, Vector3D direction) {
	this->origin = origin;
	this->direction = direction;
}

Ray::~Ray() {}

std::string Ray::toString() {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2);
	stream << "Ray: {" << endl
		<< "   Origin " << origin.toString() << endl
		<< "Direction " << direction.toString()
		<< endl << "}";
	return stream.str();
}