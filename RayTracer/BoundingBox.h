#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
class BoundingBox {
	public:
		BoundingBox();
		BoundingBox(Vector3D vmin, Vector3D vmax);

		Vector3D vmin;
		Vector3D vmax;

		enum AXIS { AXIS_X, AXIS_Y, AXIS_Z };

		bool intersect(const Ray ray, float& distance) const;
		bool overlaps(const BoundingBox bBox) const;
		bool contains(const Vector3D point) const;

		Vector3D getCentre() const;
		int getLongestAxis() const;

		friend std::ostream& operator<<(std::ostream& os, const BoundingBox& rhs);
};
#endif //BOUNDINGBOX_H
