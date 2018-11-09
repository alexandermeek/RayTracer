#include "pch.h"
#include "IntensityRGB.h"

#include <sstream> // stringstream

IntensityRGB::IntensityRGB() {
	this->r = 1;
	this->g = 1;
	this->b = 1;
}

IntensityRGB::IntensityRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

IntensityRGB::~IntensityRGB() {
}

IntensityRGB IntensityRGB::operator*(const float k) {
	IntensityRGB tempIntensity;
	if (k < 0) {
		return tempIntensity;
	}
	tempIntensity.r = r * k;
	tempIntensity.g = g * k;
	tempIntensity.b = b * k;
	return tempIntensity;
}

IntensityRGB IntensityRGB::operator+(const IntensityRGB intensity) {
	IntensityRGB tempIntensity;
	tempIntensity.r = r + intensity.r;
	tempIntensity.g = g + intensity.g;
	tempIntensity.b = b + intensity.b;
	return tempIntensity;
}

std::string IntensityRGB::toString() {
	std::stringstream stream;
	stream << r << " " << g << " " << b;
	return stream.str();
}
