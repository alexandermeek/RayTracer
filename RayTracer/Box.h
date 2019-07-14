#ifndef BOX_H
#define BOX_H
class Box : public BoundingBox, public Object3D {
	public:

		Box();
		Box(const Box &box);
		Box(Vector3D vmin, Vector3D vmax);
		Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS);

		virtual bool intersect(const Ray ray, float& distance) const;
		virtual bool intersect(const Ray ray, Vector3D& point, Vector3D& normal, float& distance) const;
		virtual Vector3D getNormal(Vector3D point) const;
		virtual BoundingBox getBoundingBox() const;

		Box operator=(const Box &box);

		friend std::ostream& operator<<(std::ostream& os, const Box& rhs);
};
#endif // BOX_H

