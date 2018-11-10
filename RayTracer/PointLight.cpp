#include "pch.h"
#include "PointLight.h"

PointLight::PointLight(Vector3D position, FloatRGB intensity) {
	this->position = position;
	this->intensity = intensity;
}

PointLight::~PointLight() {

}

Vector3D PointLight::getPosition() {
	return position;
}

FloatRGB PointLight::getIntensity() {
	return intensity;
}