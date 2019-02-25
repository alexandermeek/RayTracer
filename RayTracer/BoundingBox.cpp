#include "pch.h"
#include "BoundingBox.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(Vector3D vmin, Vector3D vmax) {
	this->vmin = vmin;
	this->vmax = vmax;
}

BoundingBox::~BoundingBox() {}

bool BoundingBox::intersect(const Ray ray, float& distance) {
	Vector3D t0 = (vmin - ray.origin) / ray.direction;
	Vector3D t1 = (vmax - ray.origin) / ray.direction;

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	bool invDirNegative = ray.direction.inverse().x < 0;
	tmin = invDirNegative ? t1.x : t0.x;
	tmax = invDirNegative ? t0.x : t1.x;

	invDirNegative = ray.direction.inverse().y < 0;
	tymin = invDirNegative ? t1.y : t0.y;
	tymax = invDirNegative ? t0.y : t1.y;

	invDirNegative = ray.direction.inverse().z < 0;
	tzmin = invDirNegative ? t1.z : t0.z;
	tzmax = invDirNegative ? t0.z : t1.z;

	if (tmin > tymax || tymin > tmax) return false;
	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;


	if (tmin > tzmax || tzmin > tmax) return false;
	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	float t = tmin;
	if (t < 0) {
		t = tmax;
		if (t < 0) return false;
	}

	distance = t;

	return true;
}

bool BoundingBox::overlaps(const BoundingBox box) {
	if (box.vmax.x < vmin.x || vmax.x < box.vmin.x) return false;
	if (box.vmax.y < vmin.y || vmax.y < box.vmin.y) return false;
	if (box.vmax.z < vmin.z || vmax.z < box.vmin.z) return false;
	return true;
}

bool BoundingBox::contains(const Vector3D point) {
	if (point.x > vmax.x || point.x < vmin.x) return false;
	if (point.y > vmax.y || point.y < vmin.y) return false;
	if (point.z > vmax.z || point.z < vmin.z) return false;
	return true;
}

Vector3D BoundingBox::getCentre() {
	float x, y, z;
	x = vmin.x + ((vmax.x - vmin.x) / 2.0f);
	y = vmin.y + ((vmax.y - vmin.y) / 2.0f);
	z = vmin.z + ((vmax.z - vmin.z) / 2.0f);
	return Vector3D(x, y, z);
}

int BoundingBox::getLongestAxis() {
	float dx, dy, dz;
	dx = vmax.x - vmin.x;
	dy = vmax.y - vmin.y;
	dz = vmax.z - vmin.z;

	if (dx >= dy && dx >= dz) return AXIS_X;
	if (dy >= dx && dy >= dz) return AXIS_Y;
	if (dz >= dx && dz >= dy) return AXIS_Z;
	return AXIS_X;
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& rhs) {
	os << std::fixed << std::setprecision(2)
		<< "Box: {" << endl
		<< "   vmin " << rhs.vmin << endl
		<< "   vmax " << rhs.vmax << endl << "}";
	return os;
}