#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
	public:
		Sphere(Vector3D centre, float radius, ColourRGB colour);
		~Sphere();

		bool doesIntersect(Vector3D rayOrigin, Vector3D directionVector);
		bool intersect(Vector3D rayOrigin, Vector3D directionVector, ColourRGB& returnColour);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;
		ColourRGB colour;
		
		Vector3D getNormal(Vector3D point);
};
#endif // SPHERE_H

