#ifndef SPHERE_H
#define SPHERE_H

class Sphere : public Object3D {
	public:
		Sphere(Vector3D centre, float radius);
		Sphere(Vector3D centre, float radius, FloatRGB kA, FloatRGB kD, FloatRGB kS);

		virtual bool intersect(Ray ray, float& distance) const;
		virtual bool intersect(Ray ray, Vector3D& point, Vector3D& normal, float& distance) const;
		virtual Vector3D getNormal(Vector3D point) const;
		virtual BoundingBox getBoundingBox() const;

		friend std::ostream& operator<<(std::ostream& os, const Sphere& rhs);
	protected:
		
	private:
		Vector3D centre;
		float radius;
};
#endif // SPHERE_H