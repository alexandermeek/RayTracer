#include "pch.h"
#include "Ray.h"

Ray::Ray() {
	this->origin = Vector3D(0, 0, 0);
	this->direction = Vector3D(0, 0, 0);
}

Ray::Ray(Vector3D origin, Vector3D direction) {
	this->origin = origin;
	this->direction = direction;
}

Ray::~Ray() {}