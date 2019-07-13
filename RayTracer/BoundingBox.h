#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
class BoundingBox {
	public:
		BoundingBox();
		BoundingBox(Vector3D vmin, Vector3D vmax);
		~BoundingBox();

		Vector3D vmin;
		Vector3D vmax;

		enum AXIS { AXIS_X, AXIS_Y, AXIS_Z };

		bool intersect(const Ray ray, float& distance);
		bool overlaps(const BoundingBox bBox);
		bool contains(const Vector3D point);

		Vector3D getCentre();
		int getLongestAxis();

		friend std::ostream& operator<<(std::ostream& os, const BoundingBox& rhs);
};
#endif //BOUNDINGBOX_H
