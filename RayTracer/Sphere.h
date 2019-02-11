#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public Object3D {
	public:
		Sphere(Vector3D centre, float radius);
		Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Sphere();

		bool intersect(Ray ray);
		bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		Vector3D getNormal(Vector3D point);

		std::string toString();
	protected:
		
	private:
		Vector3D centre;
		float radius;

		bool intersect(Ray ray, float& distance);
};
#endif // SPHERE_H