#include "pch.h"
#include "FloatRGB.h"

#include <sstream> // stringstream

FloatRGB::FloatRGB() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

FloatRGB::FloatRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

FloatRGB::~FloatRGB() {
}

FloatRGB FloatRGB::operator*(const float k) {
	FloatRGB temp;
	if (k < 0) {
		return temp;
	}
	temp.r = r * k;
	temp.g = g * k;
	temp.b = b * k;
	return temp;
}

FloatRGB FloatRGB::operator*(const FloatRGB intensity) {
	FloatRGB tempIntensity;
	tempIntensity.r = r * intensity.r;
	tempIntensity.g = g * intensity.g;
	tempIntensity.b = b * intensity.b;
	return tempIntensity;
}

FloatRGB FloatRGB::operator+(const FloatRGB intensity) {
	FloatRGB tempIntensity;
	tempIntensity.r = r + intensity.r;
	tempIntensity.g = g + intensity.g;
	tempIntensity.b = b + intensity.b;
	return tempIntensity;
}

std::string FloatRGB::toString() {
	std::stringstream stream;
	stream << r << " " << g << " " << b;
	return stream.str();
}
