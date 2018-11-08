#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
	public:
		Sphere(Vector3D centre, float radius, ColourRGB colour);
		Sphere(Vector3D centre, float radius, ColourRGB colour, float kA, float kD, float kS);
		~Sphere();

		bool intersect(Vector3D rayOrigin, Vector3D directionVector, Vector3D lightPos, ColourRGB& returnColour);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;
		ColourRGB colour;
		
		float kA;
		float kD;
		float kS;
		
		Vector3D getNormal(Vector3D point);
};
#endif // SPHERE_H

