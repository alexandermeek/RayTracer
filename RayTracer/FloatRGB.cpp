#include "pch.h"
#include "FloatRGB.h"

#include <sstream> // stringstream

FloatRGB::FloatRGB() : r(0), g(0), b(0) {}

FloatRGB::FloatRGB(const float r, const float g, const float b) 
	: r(r), g(g), b(b) {}

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

std::ostream& operator<<(std::ostream& os, const FloatRGB& rhs) {
	os << rhs.r << " " << rhs.g << " " << rhs.b;
	return os;
}
