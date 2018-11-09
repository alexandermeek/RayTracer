#ifndef OBJECT3D_H
#define OBJECT3D_H

class Object3D
{
	public:
		Object3D(ColourRGB colour, float kA, float kD, float kS);
		~Object3D();

		ColourRGB getColour();
		float getKA();
		float getKD();
		float getKS();

		virtual bool intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point);
		virtual Vector3D getNormal(Vector3D point);

		virtual std::string toString();
	private:
		ColourRGB colour;
		float kA;
		float kD;
		float kS;
};
#endif // OBJECT3D_H