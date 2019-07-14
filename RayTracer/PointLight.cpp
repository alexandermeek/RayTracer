#include "pch.h"
#include "PointLight.h"

#include <iomanip> // setprecision
#include <sstream> // stringstream

using std::endl;

PointLight::PointLight(Vector3D position, FloatRGB intensity) : LightSource(position, intensity) {}

float PointLight::calculateShadow(KDNode* kDNode, Vector3D point, 
	float& origin_offset) const {
	
	Vector3D lightDirection = (position - point).unitVector();

	Ray shadowRay(point, lightDirection);

	float miss = 1;
	{	
		Vector3D temp_point, temp_normal;
		Object3D* hitObject;
		float distance(INT32_MAX);
		bool hit = kDNode->intersect(kDNode, shadowRay, &hitObject, temp_point, temp_normal, distance, origin_offset);

		if (hit) {
			miss = 0.1;
		}
	}
	
	return miss;
}

std::ostream& operator<<(std::ostream& os, const PointLight& rhs) {
	os << std::fixed << std::setprecision(2)
		<< "PointLight: {" << endl
		<< " Position " << rhs.position << endl
		<< "       Intensity: " << rhs.intensity << endl
		<< "}";
	return os;
}