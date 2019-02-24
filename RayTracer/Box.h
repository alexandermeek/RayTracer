#ifndef BOX_H
#define BOX_H

class Box : public BoundingBox, public Object3D {
	public:

		Box();
		Box(const Box &box);
		Box(Vector3D vmin, Vector3D vmax);
		Box(Vector3D vmin, Vector3D vmax, FloatRGB kA, FloatRGB kD, FloatRGB kS);
		~Box();

		bool intersect(const Ray ray, Vector3D& point, Vector3D& normal, float& distance);
		Vector3D getNormal(Vector3D point);
		BoundingBox getBoundingBox() const;

		Box operator=(const Box &box);

		std::string toString() const;
		friend std::ostream& operator<<(std::ostream& os, const Box& rhs);
};
#endif // BOX_H

