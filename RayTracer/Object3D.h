#ifndef OBJECT3D_H
#define OBJECT3D_H

class Object3D
{
	public:
		Object3D(FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Object3D();

		FloatRGB getKA();
		FloatRGB getKD();
		FloatRGB getKS();

		virtual bool intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance);
		virtual Vector3D getNormal(Vector3D point);

		virtual std::string toString();
	private:
		FloatRGB kA;
		FloatRGB kD;
		FloatRGB kS;
};
#endif // OBJECT3D_H