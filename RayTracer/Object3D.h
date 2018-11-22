#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>

class Object3D
{
	public:
		Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Object3D();

		FloatRGB getKA();
		FloatRGB getKD();
		FloatRGB getKS();

		virtual bool intersect(Vector3D rayOrigin, Vector3D directionVector);
		virtual bool intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance, PointLight& light, FloatRGB& colour);
		virtual Vector3D getNormal(Vector3D point);

		virtual std::string toString();
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
	protected:
		FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, Vector3D normal, PointLight& light, Vector3D rayOrigin);
		virtual FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, PointLight& light, Vector3D rayOrigin);
};
#endif // OBJECT3D_H