#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
	public:
		Sphere(Vector3D centre, float radius, ColourRGB colour);
		Sphere(Vector3D centre, float radius, ColourRGB colour, float kA, float kD, float kS);
		~Sphere();

		ColourRGB getColour();
		float getKA();
		float getKD();
		float getKS();

		bool intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D& point);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;
		ColourRGB colour;
		
		float kA;
		float kD;
		float kS;
};
#endif // SPHERE_H

