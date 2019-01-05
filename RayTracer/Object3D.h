#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>

class Object3D
{
	public:
		Object3D();
		Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS, bool useBidirectionalLight);
		~Object3D();

		FloatRGB getKA();
		FloatRGB getKD();
		FloatRGB getKS();
		void setKA(FloatRGB kA);
		void setKD(FloatRGB kD);
		void setKS(FloatRGB kS);

		virtual bool intersect(Vector3D rayOrigin, Vector3D directionVector);
		virtual bool intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, Vector3D& normal, float& distance, PointLight& light);
		virtual Vector3D getNormal(Vector3D point);

		FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, Vector3D normal, PointLight& light, Vector3D rayOrigin);

		virtual std::string toString(); 
	protected:
		const float EPSILON = 0.00001;
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
		bool useBidirectionalLight;
};
#endif // OBJECT3D_H