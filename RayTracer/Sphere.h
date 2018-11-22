#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public Object3D {
	public:
		Sphere(Vector3D centre, float radius);
		Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Sphere();

		bool intersect(Vector3D rayOrigin, Vector3D directionVector);
		bool intersect(std::vector<Object3D*>& objects, Vector3D rayOrigin, Vector3D directionVector, Vector3D& point, float& distance,
			PointLight& light, FloatRGB& colour);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;

		FloatRGB getColourValue(std::vector<Object3D*>& objects, Vector3D point, PointLight& light, Vector3D rayOrigin);
};
#endif // SPHERE_H