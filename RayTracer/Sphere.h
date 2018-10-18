#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
	public:
		Sphere(Vector3D centre, float radius);
		~Sphere();

		bool doesIntersect(Vector3D rayOrigin, Vector3D directionVector);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;
};
#endif // SPHERE_H

