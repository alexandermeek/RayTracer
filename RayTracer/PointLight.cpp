#include "pch.h"
#include "PointLight.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

PointLight::PointLight(Vector3D position, FloatRGB intensity) {
	this->position = position;
	this->intensity = intensity;
}

PointLight::~PointLight() {}

std::ostream& operator<<(std::ostream& os, const PointLight& rhs) {
	os << std::fixed << std::setprecision(2)
		<< "PointLight: {" << endl
		<< " Position " << rhs.position << endl
		<< "       Intensity: " << rhs.intensity << endl
		<< "}";
	return os;
}