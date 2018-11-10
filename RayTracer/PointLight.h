#pragma once
class PointLight
{
	public:
		PointLight(Vector3D position, FloatRGB intensity);
		~PointLight();

		Vector3D getPosition();
		FloatRGB getIntensity();
	private:
		Vector3D position;
		FloatRGB intensity;
};

