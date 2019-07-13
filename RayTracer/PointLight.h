#pragma once
class PointLight
{
	public:
		PointLight(Vector3D position, FloatRGB intensity);

		Vector3D position;
		FloatRGB intensity;

		friend std::ostream& operator<<(std::ostream& os, const PointLight& rhs);
};

