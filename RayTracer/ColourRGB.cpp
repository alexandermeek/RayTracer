#include "pch.h"
#include "ColourRGB.h"

#include <sstream> // stringstream

ColourRGB::ColourRGB() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

ColourRGB::ColourRGB(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

ColourRGB::~ColourRGB() {
}

ColourRGB ColourRGB::operator*(const float k) {
	ColourRGB tempColour;
	if (k < 0) {
		return tempColour;
	}
	tempColour.r = r * k;
	tempColour.g = g * k;
	tempColour.b = b * k;
	return tempColour;
}

ColourRGB ColourRGB::operator+(const ColourRGB colour) {
	ColourRGB tempColour;
	tempColour.r = r + colour.r;
	tempColour.g = g + colour.g;
	tempColour.b = b + colour.b;
	return tempColour;
}

std::string ColourRGB::toString() {
	std::stringstream stream;
	stream << r << " " << g << " " << b;
	return stream.str();
}